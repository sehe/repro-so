#include <string>
//#include "bla.hh"
#include "api/Compiler.hh"
#include "api/DataFile.hh"
#include "api/Decoder.hh"
#include "api/Encoder.hh"
#include "api/Generic.hh"
#include "api/Stream.hh"

namespace c {
    struct cpx {
        std::string re;
        std::string im;
        cpx() :
            re(std::string()),
            im(std::string())
        { }
    };
}

namespace avro {
template<>
struct codec_traits<c::cpx>
{
    static void encode(Encoder& e, const c::cpx& v)
    {
        avro::encode(e, v.re);
        avro::encode(e, v.im);
    }
    static void decode(Decoder& d, c::cpx& v)
    {
        if(avro::ResolvingDecoder* rd =
               dynamic_cast<avro::ResolvingDecoder*>(&d))
        {
            const std::vector<size_t> fo = rd->fieldOrder();
            for(std::vector<size_t>::const_iterator it = fo.begin();
                it != fo.end();
                ++it)
            {
                switch(*it)
                {
                case 0: avro::decode(d, v.re); break;
                case 1: avro::decode(d, v.im); break;
                default: break;
                }
            }
        } else
        {
            avro::decode(d, v.re);
            avro::decode(d, v.im);
        }
    }
};
} // namespace avro

#include <stdlib.h>

int main()
{
    std::unique_ptr<avro::OutputStream> out =
        avro::memoryOutputStream();
    avro::EncoderPtr e = avro::binaryEncoder();
    e->init(*out);
    c::cpx c1;
    c1.re = "hello";
    c1.im = "thanks";
    avro::encode(*e, c1);

    std::unique_ptr<avro::InputStream> in =
        avro::memoryInputStream(*out);
    avro::DecoderPtr d = avro::binaryDecoder();
    d->init(*in);

    c::cpx c2;
    avro::decode(*d, c2);
    std::cout << '(' << c2.re << ", " << c2.im << ')' << std::endl;
    std::cout << "DECODED" << std::endl;
    return 0;
}
