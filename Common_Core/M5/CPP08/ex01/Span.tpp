#ifndef SPAN_TPP
#define SPAN_TPP

#include <iterator>
#include "Span.hpp"

template <typename Iterator>
void Span::addNumbers(Iterator begin, Iterator end) {
	const long count = static_cast<long>(std::distance(begin, end));
	if (count < 0 || static_cast<size_t>(count) > _maxSize - _numbers.size()) {
		throw SpanException("Not enough space in Span to add the whole range!");
	}
	for (Iterator it = begin; it != end; ++it) {
		addNumber(*it);
	}
}

#endif