#ifndef PARSE_H
#define PARSE_H

#include "card.h"
#include "../net/udp.h"

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

void pkg_cards(CARD **, char *);
void unpkg_cards(char *, CARD **);

#endif