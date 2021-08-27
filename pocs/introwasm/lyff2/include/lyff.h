/*
 * Copyright 2017 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
#ifndef LYFF_H
#define LYFF_H

typedef unsigned char byte;

#define DIM 100
#define SIZE ((DIM + 2) * (DIM + 2) / 8)  // byte size

// Gets the cell on the default board.
byte get_cell(int x, int y);

// Sets a cell on a board.
void set_cell_ref(byte *b, int x, int y);

// Clears a board.
void clear_board_ref(byte *b);

// Steps through one iteration of Conway's Game of Life. Returns the number of now alive cells, or
// -1 if no cells changed this iteration: i.e., stable game.
int board_step();

// Count the total number of alive cells.
int board_count();
// Returns the pointer location of the rendered board.
byte *board_ref();

// Clears the board.
void board_init();
#endif
