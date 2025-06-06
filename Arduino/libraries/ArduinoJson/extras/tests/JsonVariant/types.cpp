// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2025, Benoit BLANCHON
// MIT License

#include <ArduinoJson.h>
#include <stdint.h>
#include <catch.hpp>
#include <limits>

#include "Allocators.hpp"
#include "Literals.hpp"

template <typename T>
void checkReference(T& expected) {
  JsonVariant variant = expected;
  REQUIRE(expected == variant.as<T&>());
}

template <typename T>
void checkNumericType() {
  JsonDocument docMin, docMax;
  JsonVariant variantMin = docMin.to<JsonVariant>();
  JsonVariant variantMax = docMax.to<JsonVariant>();

  T min = std::numeric_limits<T>::min();
  T max = std::numeric_limits<T>::max();

  variantMin.set(min);
  variantMax.set(max);

  REQUIRE(min == variantMin.as<T>());
  REQUIRE(max == variantMax.as<T>());
}

TEST_CASE("JsonVariant set()/get()") {
  SpyingAllocator spy;
  JsonDocument doc(&spy);
  JsonVariant variant = doc.to<JsonVariant>();

#if ARDUINOJSON_USE_LONG_LONG
  SECTION("SizeOfJsonInteger") {
    REQUIRE(8 == sizeof(JsonInteger));
  }
#endif

  // /!\ Most test were moved to `JsonVariant/set.cpp`
  // TODO: move the remaining tests too

  SECTION("False") {
    variant.set(false);
    REQUIRE(variant.as<bool>() == false);
    REQUIRE(spy.log() == AllocatorLog{});
  }

  SECTION("True") {
    variant.set(true);
    REQUIRE(variant.as<bool>() == true);
    REQUIRE(spy.log() == AllocatorLog{});
  }

  SECTION("Double") {
    checkNumericType<double>();
  }
  SECTION("Float") {
    checkNumericType<float>();
  }
  SECTION("SChar") {
    checkNumericType<signed char>();
  }
  SECTION("SInt") {
    checkNumericType<signed int>();
  }
  SECTION("SLong") {
    checkNumericType<signed long>();
  }
  SECTION("SShort") {
    checkNumericType<signed short>();
  }
  SECTION("UChar") {
    checkNumericType<unsigned char>();
  }
  SECTION("UInt") {
    checkNumericType<unsigned int>();
  }
  SECTION("ULong") {
    checkNumericType<unsigned long>();
  }
  SECTION("UShort") {
    checkNumericType<unsigned short>();
  }
#if ARDUINOJSON_USE_LONG_LONG
  SECTION("LongLong") {
    checkNumericType<unsigned long long>();
  }
  SECTION("ULongLong") {
    checkNumericType<unsigned long long>();
  }
#endif

  SECTION("Int8") {
    checkNumericType<int8_t>();
  }
  SECTION("Uint8") {
    checkNumericType<uint8_t>();
  }
  SECTION("Int16") {
    checkNumericType<int16_t>();
  }
  SECTION("Uint16") {
    checkNumericType<uint16_t>();
  }
  SECTION("Int32") {
    checkNumericType<int32_t>();
  }
  SECTION("Uint32") {
    checkNumericType<uint32_t>();
  }
#if ARDUINOJSON_USE_LONG_LONG
  SECTION("Int64") {
    checkNumericType<int64_t>();
  }
  SECTION("Uint64") {
    checkNumericType<uint64_t>();
  }
#endif

  SECTION("CanStoreObject") {
    JsonDocument doc2;
    JsonObject object = doc2.to<JsonObject>();

    variant.set(object);
    REQUIRE(variant.is<JsonObject>());
    REQUIRE(variant.as<JsonObject>() == object);
  }
}

TEST_CASE("volatile") {
  JsonDocument doc;
  JsonVariant variant = doc.to<JsonVariant>();

  SECTION("volatile bool") {  // issue #2029
    volatile bool f = true;
    variant.set(f);
    CHECK(variant.is<bool>() == true);
    CHECK(variant.as<bool>() == true);
  }

  SECTION("volatile int") {
    volatile int f = 42;
    variant.set(f);
    CHECK(variant.is<int>() == true);
    CHECK(variant.as<int>() == 42);
  }

  SECTION("volatile float") {  // issue #1557
    volatile float f = 3.14f;
    variant.set(f);
    CHECK(variant.is<float>() == true);
    CHECK(variant.as<float>() == 3.14f);
  }

  SECTION("volatile double") {
    volatile double f = 3.14;
    variant.set(f);
    CHECK(variant.is<double>() == true);
    CHECK(variant.as<double>() == 3.14);
  }
}
