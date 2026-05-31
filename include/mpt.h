#pragma once

#include <cstdint>

#include "include/blob.h"

struct extension_node {
  uint8_t prefix;
  branch_node* next;
};

struct branch_node {
};

struct leaf_node {
  uint8_t prefix;

};