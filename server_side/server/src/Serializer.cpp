#include "Serializer.hpp"

void Serializer::save(boost::asio::streambuf& readBuf, Request& req) {
    std::istream is(&readBuf);
    boost::archive::binary_iarchive ar(is);
    ar& req;
}

void Serializer::load(boost::asio::streambuf& writeBuf, Reply& rep) {
    std::ostream os(&writeBuf);
    boost::archive::binary_oarchive ar(os);
    ar& rep;
}
