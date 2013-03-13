#ifndef PANLIB_ET_LITERAL_H
#define PANLIB_ET_LITERAL_H

#include <utility>

#include "terminal.h"

namespace panlib{
namespace ET{

template<typename T>
terminal<T> lit(T &&value){
	return { std::forward<T>(value) };
}

} //namespace ET
} //namesapce panlib

#endif

