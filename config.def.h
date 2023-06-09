#ifndef __config_h

enum {
  ITEM,
  TITLE,
  LINK,
  DESC,
};

unsigned int CONTENT_LEN = 2048; // max length of any field's contents

/** tags are all sans braces */
#define CHANNEL_TAG "channel"

#define ITEM_TAG  "article"
#define TITLE_TAG "h1"
#define LINK_TAG  "link"
#define DESC_TAG  "text"

/** HTML tag <-> XML tag */
const char* TYPES[4][2] = {
  {ITEM_TAG,  "item"},
  {TITLE_TAG, "title"},
  {LINK_TAG,  "link"},
  {DESC_TAG,  "description"},
};

#define __config_h
#endif
