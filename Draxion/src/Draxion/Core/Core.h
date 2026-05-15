#pragma once
#include <memory>

#define DRX_API

class xyz {};

namespace Draxion
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T>
	using Ref = std::shared_ptr<T>;

}