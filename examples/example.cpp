#include <sklib/uuid.hpp>
#include <assert.h>
#include <unordered_set>

using namespace sklib;

int main()
{
    // create a NIL UUID
    Uuid uuid1 = Uuid::Nil();
    // check if a UUID is Nil
    assert(uuid1.IsNil());

    // generate a new UUID
    Uuid uuid2;
    // validate a UUID (same as !Uuid::IsNil())
    assert(uuid2);
    // compare two UUIDs
    assert(uuid1 != uuid2);

    // parse a UUID from a string
    assert(Uuid::FromString("646dcdae-0c7f-4070-8323-b20578c9339f", uuid1) && !uuid1.IsNil());

    // stringify a UUID
    std::string str;
    assert(Uuid::ToString(str, uuid1) && !str.empty());

    // hash a UUID
    assert(uuid1.Hash() != 0);

    // std::hash adapter which uses Uuid::Hash(), so a UUID can be used for hash maps / sets
    std::unordered_set<sklib::Uuid> uuids;

    return 0;
}
