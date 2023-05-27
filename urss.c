#include "config.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int
consume_until_tag(const char* tag, char* content) {
  /** determine tag */ 
  int i = 0; // stream index
  int j = 0; // content index  
  char k;
  int len = strlen(tag);
  while(read(0, &k, 1) > 0) { 
    switch(k) {
      case '>': // time to compare tags
        if (i == len)
          return j;
      default: 
        if (tag[i] != k)
          i = 0;
        else
          i++;
    } 
    /** record to string */ 
    if (content != NULL && k != '\n') { 
      content[j] = k;
      j++;
    }
  }
  return -1; 
}

void
export_content(int type) {
  consume_until_tag(TYPES[type][0], NULL); 
  char content[CONTENT_LEN]; 
  int j = consume_until_tag(TYPES[type][0], content);
  /**
   * j (end) 
   * - length of type
   * - closing '</'
   */
  content[j - strlen(TYPES[type][0]) - 2] = '\0'; // clean up closing tag
  printf("<%s><![CDATA[%s]]></%s>\n", TYPES[type][1], content, TYPES[type][1]);
}

int
main(void) { 
  /**
   * We need to consume until we have an item, and then consume within that
   * ideally, we'd only read a given stream once: we shouldn't make a bunch of substrings
   * this means that we need to loop over consume_until_tag until there's a new tag, and treat that as the scope
   * export_content will only be useful for the itera-item content
   * we only need to make one substring -- consume_until_tag includes part of the closing tag, so we need to remove it
   */
  /** echo beginning of RSS feed */
  printf("<rss version=\"0.92\">\n<channel>\n%s\n", CHANNEL_PREFIX);
  while (consume_until_tag(ITEM_TAG, NULL) != -1) { 
    printf("<item>\n");
    export_content(TITLE);
    export_content(LINK);
    export_content(DESC); 
    printf("</item>\n");
    /** go next */
    consume_until_tag(ITEM_TAG, NULL);
  }

  /** echo end of RSS feed */
  printf("</channel>\n</rss>");
  return 0;
}
