// bigfile_gen.cpp
// Compile with: g++ -O2 -std=c++17 -o bigfile_gen bigfile_gen.cpp
//
// Usage examples:
//  ./bigfile_gen --output corpus.txt --size-mb 500 --mode repeat --word hello
//  ./bigfile_gen --output corpus_rand.txt --size-mb 200 --mode random --min-len 3 --max-len 10 --seed 42
//  ./bigfile_gen --output corpus_vocab.txt --size-mb 100 --mode vocab --vocab 5000

#include <bits/stdc++.h>
using namespace std;

struct Config {
    string output = "corpus.txt";
    size_t size_mb = 100;
    string mode = "repeat"; // repeat | random | vocab
    string word = "word";
    size_t vocab = 10000;
    int min_len = 3;
    int max_len = 8;
    unsigned int seed = (unsigned int) chrono::high_resolution_clock::now().time_since_epoch().count();
    size_t chunk_bytes = 4 * 1024 * 1024; // write in 4MB chunks
};

void usage(const char* prog) {
    cerr << "Usage: " << prog << " [options]\n"
         << "Options:\n"
         << "  --output <path>       Output file path (default corpus.txt)\n"
         << "  --size-mb <n>         Target size in MB (default 100)\n"
         << "  --mode <repeat|random|vocab>\n"
         << "                        Generation mode (default repeat)\n"
         << "  --word <s>            Word to repeat in repeat mode (default 'word')\n"
         << "  --vocab <n>           Vocabulary size for vocab mode (default 10000)\n"
         << "  --min-len <n>         Min random word length (random mode)\n"
         << "  --max-len <n>         Max random word length (random mode)\n"
         << "  --seed <n>            Random seed (optional)\n"
         << "  --chunk-bytes <n>     Chunk size for buffered writes in bytes (default 4MB)\n"
         << "  --help                Show this help\n";
}

string make_random_word(mt19937 &rng, int min_len, int max_len) {
    static const char alphabet[] =
        "abcdefghijklmnopqrstuvwxyz";
    uniform_int_distribution<int> len_dist(min_len, max_len);
    uniform_int_distribution<int> char_dist(0, (int)strlen(alphabet) - 1);
    int L = len_dist(rng);
    string s;
    s.reserve(L);
    for (int i = 0; i < L; ++i) s.push_back(alphabet[char_dist(rng)]);
    return s;
}

int main(int argc, char** argv) {
    Config cfg;
    // simple arg parsing
    for (int i = 1; i < argc; ++i) {
        string a = argv[i];
        if (a == "--output" && i+1 < argc) cfg.output = argv[++i];
        else if (a == "--size-mb" && i+1 < argc) cfg.size_mb = stoull(argv[++i]);
        else if (a == "--mode" && i+1 < argc) cfg.mode = argv[++i];
        else if (a == "--word" && i+1 < argc) cfg.word = argv[++i];
        else if (a == "--vocab" && i+1 < argc) cfg.vocab = stoull(argv[++i]);
        else if (a == "--min-len" && i+1 < argc) cfg.min_len = stoi(argv[++i]);
        else if (a == "--max-len" && i+1 < argc) cfg.max_len = stoi(argv[++i]);
        else if (a == "--seed" && i+1 < argc) cfg.seed = (unsigned int)stoul(argv[++i]);
        else if (a == "--chunk-bytes" && i+1 < argc) cfg.chunk_bytes = stoull(argv[++i]);
        else if (a == "--help") { usage(argv[0]); return 0; }
        else { cerr << "Unknown or malformed arg: " << a << "\n"; usage(argv[0]); return 1; }
    }

    if (cfg.min_len < 1) cfg.min_len = 1;
    if (cfg.max_len < cfg.min_len) cfg.max_len = cfg.min_len;

    const uint64_t target_bytes = cfg.size_mb * 1024ULL * 1024ULL;
    cout << "Generating '" << cfg.output << "' ~ " << cfg.size_mb << " MB (" << target_bytes << " bytes) "
         << "mode=" << cfg.mode << " seed=" << cfg.seed << "\n";

    ios::sync_with_stdio(false);
    ofstream ofs(cfg.output, ios::binary);
    if (!ofs) { cerr << "Failed to open output file: " << cfg.output << "\n"; return 2; }

    mt19937 rng(cfg.seed);
    uniform_int_distribution<uint32_t> vocab_dist(1, (uint32_t)max<uint64_t>(1, cfg.vocab));

    string chunk;
    chunk.reserve(cfg.chunk_bytes + 1024);

    uint64_t written = 0;
    auto flush_chunk = [&]() {
        if (!chunk.empty()) {
            ofs.write(chunk.data(), (streamsize)chunk.size());
            written += (uint64_t)chunk.size();
            chunk.clear();
        }
    };

    // Pre-generate a few random words if desired (reduces generator overhead)
    vector<string> vocab_cache;
    if (cfg.mode == "vocab") {
        vocab_cache.reserve(min<uint64_t>(cfg.vocab, 100000));
        // but don't create 10M strings — limit cache size
        uint64_t cache_size = min<uint64_t>(cfg.vocab, 200000);
        for (uint64_t i = 1; i <= cache_size; ++i) {
            vocab_cache.push_back("w" + to_string(i));
        }
    }

    // Fast path for repeat mode: build big chunk consisting of the repeated word + space/newline
    if (cfg.mode == "repeat") {
        string token = cfg.word;
        if (token.empty()) token = "word";
        token += ' ';
        // craft a chunk by repeating token
        while (written < target_bytes) {
            if (chunk.capacity() - chunk.size() < token.size()) {
                // flush when chunk is full-ish
                flush_chunk();
            }
            // append token multiple times until chunk near capacity
            size_t can = (cfg.chunk_bytes > chunk.size()) ? (cfg.chunk_bytes - chunk.size()) : 0;
            if (can < token.size()) {
                flush_chunk();
                continue;
            }
            size_t repeats = can / token.size();
            // append repeats in a loop
            for (size_t r = 0; r < repeats; ++r) chunk.append(token);
        }
        // final flush and done
        flush_chunk();
        cout << "Done. written bytes: " << written << "\n";
        return 0;
    }

    // Random or vocab mode
    while (written < target_bytes) {
        // generate words until chunk near cfg.chunk_bytes
        while (chunk.size() < cfg.chunk_bytes) {
            string w;
            if (cfg.mode == "random") {
                w = make_random_word(rng, cfg.min_len, cfg.max_len);
            } else if (cfg.mode == "vocab") {
                // choose index
                uint32_t idx = vocab_dist(rng);
                if (idx <= vocab_cache.size()) w = vocab_cache[idx-1];
                else w = "w" + to_string(idx);
            } else {
                // fallback to repeat
                w = cfg.word;
                if (w.empty()) w = "word";
            }
            // append word and a space
            chunk.append(w);
            chunk.push_back(' ');
            // occasional newline to simulate lines
            if ((rng() & 0xFF) < 8) chunk.push_back('\n');
            if (chunk.size() >= cfg.chunk_bytes) break;
        }
        flush_chunk();
    }

    cout << "Done. written bytes: " << written << "\n";
    return 0;
}
