#pragma once
#include <memory>
#include <string>

namespace sklib
{
    /**
     * @brief Represents a UUID based on a system generator
     */
    class Uuid
    {
    public:
        /**
         * @brief Construct a new UUID
         */
        Uuid();
        /**
         * @brief Copy-construct a new UUID object
         */
        Uuid(const Uuid &other);
        /**
         * @brief Copy a UUID object
         */
        Uuid &operator=(const Uuid &other);
        /**
         * @brief Move-construct a new UUID object
         */
        Uuid(Uuid&&) noexcept = default;
        /**
         * @brief Move a UUID object
         */
        Uuid &operator=(Uuid&&) noexcept = default;
        /**
         * @brief Destroy a UUID object
         */
        ~Uuid();
        /**
         * @brief Parse a UUID from a string and return the result
         */
        [[nodiscard]] static bool FromString(std::string_view string, Uuid &uuid) noexcept;
        /**
         * @brief Stringify a UUID to a string and return the result
         */
        [[nodiscard]] static bool ToString(std::string &string, const Uuid &uuid) noexcept;
        /**
         * @brief Hash a UUID
         */
        [[nodiscard]] std::size_t Hash() const noexcept;
        /**
         * @brief Return a new Uuid object with a Nil-UUID
         */
        [[nodiscard]] static Uuid Nil() noexcept;
        /**
         * @brief Checks whether the UUID is Nil
         */
        [[nodiscard]] bool IsNil() const noexcept;
        /**
         * @brief Checks whether the UUID is not Nil, convenience operator for !IsNil
         */
        [[nodiscard]] operator bool() const noexcept;
        /**
         * @brief Compare two Uuid objects
         */
        [[nodiscard]] bool operator==(const Uuid &other) const noexcept;
        /**
         * @brief Compare two Uuid objects
         */
        [[nodiscard]] inline bool operator!=(const Uuid &other) const noexcept { return !(*this == other); };
    private:
        friend class std::hash<Uuid>;
        // Forward declaration of a struct containing the platform specific UUID specs / types.
        // Depending on the platform, this may be defined differently
        struct PlatformSpec;
        // Owned pointer to the platform specs; similar to the PIMPL idiom
        std::unique_ptr<PlatformSpec> spec_;
    };
}

template<>
struct std::hash<sklib::Uuid>
{
    std::size_t operator()(const sklib::Uuid &uuid)
    {
        return uuid.Hash();
    }
};
