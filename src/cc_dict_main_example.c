// Copyright (c) 2016 Lucas Nodari 
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdio.h>
#include <stdlib.h>

#include "cc_dict.h"

typedef struct dict_test_entry {
  int i;
  char c;
} dte_t;

void test_dict()
{
  comp_dict_t *dict;

  dict = dict_new();
  dict_debug_print(dict);

  dte_t dt[10] = { {1, 'a'}, {5, '['}, {4, 'm'}, {237, '-'}, {250, ':'},
  {1, '.'}, {100, 'j'}, {500, 's'}, {99, 'a'}, {19, 'x'}
  };

  dict_put(dict, "aaa", &dt[0]);
  dict_put(dict, "aab", &dt[1]);
  dict_put(dict, "abc", &dt[2]);
  dict_put(dict, "111", &dt[3]);
  dict_put(dict, "a-a", &dt[4]);
  dict_put(dict, "key", &dt[5]);
  dict_put(dict, "dict", &dt[6]);
  dict_put(dict, "bbb", &dt[7]);
  dict_put(dict, "ccc", &dt[8]);
  dict_put(dict, "test", &dt[9]);

  dict_debug_print(dict);

  dte_t *temp = dict_get(dict, "ccc");

  printf("%d %c\n", temp->i, temp->c);
  printf("%c\n", ((dte_t *) dict_remove(dict, "dict"))->c);

  dict_debug_print(dict);

  dict_remove(dict, "aaa");
  dict_remove(dict, "aab");
  dict_remove(dict, "abc");
  dict_remove(dict, "111");
  dict_remove(dict, "a-a");
  dict_remove(dict, "key");
  dict_remove(dict, "dict");
  dict_remove(dict, "bbb");
  dict_remove(dict, "ccc");
  dict_remove(dict, "test");

  dict_debug_print(dict);

  dte_t limits[20000];
  char key[10];

  int i;
  for (i = 0; i < 20000; ++i) {
    sprintf(key, "%d", i);
    limits[i].i = rand();
    limits[i].c = (char) rand();
    dict_put(dict, key, &limits[i]);
  }

  dict_debug_print(dict);

  dict_remove(dict, "5849");
  dict_remove(dict, "5505");
  dict_remove(dict, "16640");
  dict_remove(dict, "19987");
  dict_remove(dict, "3723");
  dict_remove(dict, "13208");
  dict_remove(dict, "2716");

  //dict_free(dict); // error

  for (i = 0; i < 20000; ++i) {
    sprintf(key, "%d", i);
    dict_remove(dict, key);
  }

  dict_debug_print(dict);

  dict_free(dict);
}

int main(int argc, char **argv)
{
  test_dict();
  return 0;
}
