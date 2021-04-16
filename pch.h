#ifndef PCH_H
#define PCH_H

enum class TYPE
{
    STACKARRAY, QUEUEARRAY, DEQUEARRAY, UNDEFINED
};
#include <iostream>
#include <memory>
#include <utility>
#include <optional>
#include <string>
#include <assert.h>
#include "Array.h"
#include "ItemType.h"
#include "ArrayStack.h"
#include "ArrayQueue.h"
#include "ArrayDeque.h"
#include "BDeque.h"
#include "Application.h"

#endif PCH_H