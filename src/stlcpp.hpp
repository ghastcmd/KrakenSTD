#pragma once

template <typename _ty>
void swap(_ty &f, _ty &l) { _ty ax = f; f = l; l = ax; }

template <typename _ty>
void iter_swap(_ty *f, _ty *l) { _ty ax = *f; *f = *l; *l = ax; }