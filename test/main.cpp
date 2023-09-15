#include <sklib/uuid.hpp>
#include <assert.h>
#include <unordered_set>

using namespace sklib;

int main()
{
    Uuid uuid1 = Uuid::Nil();
    assert(uuid1.IsNil());

    Uuid uuid2;
    assert(!uuid2.IsNil());
    assert(uuid1 != uuid2);

    assert(Uuid::FromString("646dcdae-0c7f-4070-8323-b20578c9339f", uuid1) && !uuid1.IsNil());

    std::string str;
    assert(Uuid::ToString(str, uuid1) && !str.empty());

    assert(uuid1.Hash() != 0);

    std::unordered_set<sklib::Uuid> uuids;

    return 0;
}
