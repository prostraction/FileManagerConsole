#include <filesystem>
#include <iostream>
#include <cstring>

#include <cmath>
#include <bits/stdc++.h>

#include <set>

void process(const std::filesystem::path &dir) {
    return;
}

/*
uint64_t m_size(const std::filesystem::path &dir) {
    std::filesystem::path p {dir};
    uintmax_t max_val = 0;

    for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{p, std::filesystem::directory_options::skip_permission_denied}) {
        try {
            if (dir_entry.is_regular_file() 
                    && dir_entry.path() != "/dev/core" 
                    && dir_entry.path() != "/proc/kcore"
                    && dir_entry.path().string().compare(1,4,"proc") != 0) {
                max_val += dir_entry.file_size();
            }
        }  catch (std::filesystem::filesystem_error& e) {
            //fprintf(stderr, "Skipped: %s\n", dir_entry.path().c_str());
        }
    }
    return max_val;
}
*/

uint64_t m_free(const std::filesystem::path &dir) {
    std::filesystem::path p {dir};
    std::filesystem::space_info si = std::filesystem::space(dir);
    uintmax_t max_val = 0;

    try {
        si = std::filesystem::space(dir);
        max_val = si.free;
    } catch (std::filesystem::filesystem_error& e) {
        fprintf(stderr, "Skipped: %s\n", p.string().c_str());
    }

    return max_val;
}

uint64_t m_capacity(const std::filesystem::path &dir) {
    std::filesystem::path p {dir};
    std::filesystem::space_info si = std::filesystem::space(dir);
    uintmax_t max_val = 0;

    try {
        si = std::filesystem::space(dir);
        max_val = si.capacity;
    } catch (std::filesystem::filesystem_error& e) {
        fprintf(stderr, "Skipped: %s\n", p.string().c_str());
    }

    return max_val;
}

std::string readable_size(uint64_t s) {
    int i{};
    double mantissa = s;
    for (; mantissa >= 1024.; mantissa /= 1024., ++i) { }
    mantissa = std::ceil(mantissa * 10.) / 10.;

    std::stringstream ss;
    ss << mantissa << " " << "BKMGTPE"[i];
    std::string returnable = ss.str();
    return returnable;
}

int main(int argc, char* argv[]) {
    switch (argc)
    {
    case 1:
        process("/");
        break;
    case 2:
        if (!strcmp(argv[1], "-m") || !strcmp(argv[1], "--measure")) {
            uint64_t free = m_free("/");
            uint64_t capacity = m_capacity("/");
            std::cout << "Size: " << readable_size(free) << "B / " <<
                readable_size(capacity) << "B\n";
            return 0;
        }
        break;
    default:
        break;
    }

}