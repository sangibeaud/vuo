/**
 * @file
 * VuoBase64 implementation, based on the work of René Nyffenegger.
 *
 * Copyright (C) 2004-2008 René Nyffenegger
 *
 * This source code is provided 'as-is', without any express or implied
 * warranty. In no event will the author be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this source code must not be misrepresented; you must not
 *    claim that you wrote the original source code. If you use this source code
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original source code.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * René Nyffenegger rene.nyffenegger@adp-gmbh.ch
 */

#include "module.h"
#include "VuoBase64.h"
#include <iostream>

#ifdef VUO_COMPILER
VuoModuleMetadata({
					  "title" : "VuoBase64"
				 });
#endif

/**
 * The 64 characters part of the Base64 encoding set.
 */
static const std::string base64_chars =
			 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			 "abcdefghijklmnopqrstuvwxyz"
			 "0123456789+/";

/**
 * Returns true if the character is one of the 64 characters part of the Base64 encoding set.
 */
static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

/**
 * Converts `data` (raw 8-bit binary data) into ASCII Base64 text with a null-terminator.
 *
 * The caller is responsible for freeing the returned string.
 */
char *VuoBase64_encode(long long in_len, char const *bytes_to_encode)
{
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
	char_array_3[i++] = *(bytes_to_encode++);
	if (i == 3) {
	  char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
	  char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
	  char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
	  char_array_4[3] = char_array_3[2] & 0x3f;

	  for(i = 0; (i <4) ; i++)
		ret += base64_chars[char_array_4[i]];
	  i = 0;
	}
  }

  if (i)
  {
	for(j = i; j < 3; j++)
	  char_array_3[j] = '\0';

	char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
	char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
	char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
	char_array_4[3] = char_array_3[2] & 0x3f;

	for (j = 0; (j < i + 1); j++)
	  ret += base64_chars[char_array_4[j]];

	while((i++ < 3))
	  ret += '=';

  }

  return strdup(ret.c_str());
}

/**
 * Converts `text` (ASCII Base64 text) into raw 8-bit binary data, and outputs the number of decoded bytes in `outputLength`.
 *
 * The caller is responsible for freeing the returned string.
 */
char *VuoBase64_decode(char const *encoded_string, long long *outputLength)
{
  int in_len = strlen(encoded_string);
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=')) {
	if (encoded_string[in_] == '\\' || encoded_string[in_] == '\n')
	{
		in_++;
		continue;
	}

	if (!is_base64(encoded_string[in_]))
		break;

	char_array_4[i++] = encoded_string[in_]; in_++;
	if (i ==4) {
	  for (i = 0; i <4; i++)
		char_array_4[i] = base64_chars.find(char_array_4[i]);

	  char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
	  char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
	  char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

	  for (i = 0; (i < 3); i++)
		ret += char_array_3[i];
	  i = 0;
	}
  }

  if (i) {
	for (j = i; j <4; j++)
	  char_array_4[j] = 0;

	for (j = 0; j <4; j++)
	  char_array_4[j] = base64_chars.find(char_array_4[j]);

	char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
	char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
	char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

	for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  *outputLength = ret.length();
  char *data = (char *)malloc(*outputLength);
  memcpy(data, ret.data(), *outputLength);
  return data;
}
