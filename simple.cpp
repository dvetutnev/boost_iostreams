#include <gtest/gtest.h>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <algorithm>
#include <memory>

std::string read_stream(std::istream& strm) {
    std::string ret;
    while(strm) {
        char buff[1024];
        strm.read(buff, sizeof(buff));
        auto count = strm.gcount();
        if (count > 0) {
            ret.append(buff, static_cast<std::size_t>(count));
        }
    }
    return ret;
}

using ArraySource = boost::iostreams::array_source;
using StreamArray = boost::iostreams::stream<ArraySource>;

TEST(Fake, convertible_2_std_istream)
{
    const std::string input = "sgr\ng\tanm;lj;zjgv;es\\eeebbvthj";
    ArraySource arr{input.data(), input.size()};
    StreamArray strm{arr};
    std::string result = read_stream(strm);
    ASSERT_EQ(result, input);
}

TEST(Fake, copy_input)
{
    const char* input = "sgr\ng\tanm;lj;zjgv;es\\eeebbvthj";
    const std::size_t count = sizeof(input);
    auto data = std::make_unique<char[]>(count);
    std::copy_n(input, count, data.get());
    ASSERT_EQ(std::string{data.get()}, input);
    ArraySource arr{data.get(), count - 1};
    //data.reset();
    StreamArray strm{arr};
    std::string result = read_stream(strm);
    ASSERT_EQ(result, input);
}
