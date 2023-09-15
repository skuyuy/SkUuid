#include <sklib/uuid.hpp>

// WINDOWS implementation
#include <Windows.h>
#pragma comment(lib, "rpcrt4.lib")

namespace
{
    // helper string conversion, since codecvt is deprecated

    std::wstring string_to_wstring(std::string_view str)
    {
        std::wstring result;
        MultiByteToWideChar(CP_UTF8, 0, str.data(), str.length(), result.data(), 0);

        return result;
    }

    std::string wstring_to_string(std::wstring_view str)
    {
        std::string result;
        WideCharToMultiByte(CP_ACP, 0, str.data(), str.length(), result.data(), 0, 0, FALSE);

        return result;
    }
}

namespace sklib
{

struct Uuid::PlatformSpec
{
    UUID uuid;
};

Uuid::Uuid():
    spec_{std::make_unique<PlatformSpec>()}
{
    UuidCreate(&spec_->uuid);
}

Uuid::Uuid(const Uuid &other):
    spec_{std::make_unique<PlatformSpec>(*other.spec_)}
{}

Uuid &Uuid::operator=(const Uuid &other)
{
    spec_ = std::make_unique<PlatformSpec>(*other.spec_);
    return *this;
}

Uuid::~Uuid() = default;

bool Uuid::FromString(std::string_view string, Uuid &uuid) noexcept
{
#ifdef UNICODE
    auto wstr = string_to_wstring(string.data());
    auto result = UuidFromStringW(reinterpret_cast<RPC_WSTR>(wstr.data()), &uuid.spec_->uuid);
#else
    std::string str(string);
    auto result = UuidFromStringA(reinterpret_cast<RPC_CSTR>(str.data()), &uuid.spec_->uuid);
#endif
    return result == RPC_S_OK;
}

bool Uuid::ToString(std::string &string, const Uuid &uuid) noexcept
{
#ifdef UNICODE
    std::wstring wstr;
    RPC_WSTR uuid_str = nullptr;
    // we can assume this returns RPC_S_OK because else the system is just out of memory
    if(UuidToStringW(&uuid.spec_->uuid, &uuid_str) == RPC_S_OK)
    {
        wstr = reinterpret_cast<wchar_t*>(uuid_str);
        string = wstring_to_string(wstr);
        return true;
    }
#else
    std::string wstr;
    RPC_CSTR uuid_str = nullptr;
    // we can assume this returns RPC_S_OK because else the system is just out of memory
    if(UuidToStringA(&uuid.spec_->uuid, &uuid_str) == RPC_S_OK)
    {
        string = reinterpret_cast<char*>(uuid_str);
        return true;
    }
#endif
    return false;
}

Uuid Uuid::Nil() noexcept
{
    Uuid new_uuid;
    UuidCreateNil(&new_uuid.spec_->uuid);
    return new_uuid;
}

bool Uuid::IsNil() const noexcept
{
    RPC_STATUS status;
    return UuidIsNil(&spec_->uuid, &status);
}

Uuid::operator bool() const noexcept
{
    return !IsNil();
}

bool Uuid::operator==(const Uuid &other) const noexcept
{
    RPC_STATUS status;
    return UuidEqual(&spec_->uuid, &other.spec_->uuid, &status);
}

std::size_t Uuid::Hash() const noexcept
{
    RPC_STATUS status;
    return UuidHash(&spec_->uuid, &status);
}

}
