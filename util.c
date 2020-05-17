
#include "util.h"

struct Subs *subs_get (struct Subs *head, long cts)
{
  struct Subs *node;
  if (!head)
    return NULL;
  for (node = head; node && cts > node->smsts; node = node->next)
    ;
  if (node)
    return node->prev;
  return NULL;
}

struct Subs *subs_clear (struct Subs *subs)
{
    struct Subs *ptr;
    if (!subs)
        return CELL_OK;
    for (ptr = subs; ptr != NULL; ptr = subs)
    {
        subs = ptr->next;
        if (ptr->text)
            free (ptr->text);
        free (ptr);
    }
    return NULL;
}
/* SRT sub format:
1097\n
01:20:45,138 --> 01:20:48,164\n
You'd say anything now\n
to get what you want.\n
\n
-- elements:
1 sub index
2 time index: start --> end
3 text
3 text
4 <empty line>
*/
struct Subs *subs_load (char *path)
{
  FILE *srtf;
  struct Subs *head = NULL;
  struct Subs *node = NULL;
  if (NULL == (srtf = fopen (path, "r")))
  {
    Nprintf ("subs_load can't open SRT '%s'\n", path);
    return NULL;
  }
  char *tmbuff = (char *)malloc (1024);
  if (NULL == tmbuff)
  {
    Nprintf ("subs_load can't malloc 1024b\n");
    return NULL;
  }
  /* load subtitles one by one */
  int elemidx = 1;  //element index: 1, 2, 3, 4
  int subidx;
  int subcnt = 0;
  long sts, ets;
  char *subtext = tmbuff + 512;
  int stidx = 0;
  int te[8];
  //Nprintf ("subs_load processing SRT '%s'\n", path);
  while (fgets (tmbuff, 511, srtf) != NULL)
  {
    char *ptp = tmbuff;
    //if (subcnt > 20)
    //    break;
    //Nprintf ("subs_load process line: '%s'\n", ptp);
    switch (elemidx)
    {
      case 1:
        //set sub index
        subidx = atoi (ptp);
        //Nprintf ("index: %d\n", subidx);
        elemidx++;
      break;
      case 2:
        //reformat time
        if (sscanf (ptp, "%d:%d:%d,%d --> %d:%d:%d,%d", &te[0], &te[1], &te[2], &te[3], &te[4], &te[5], &te[6], &te[7]) == 8)
        {
          //Nprintf ("times: %d:%d:%d.%d > %d:%d:%d.%d\n", te[0], te[1], te[2], te[3], te[4], te[5], te[6], te[7]);
          sts = (te[0] * 3600 + te[1] * 60 + te[2]) * 1000 + te[3];
          ets = (te[4] * 3600 + te[5] * 60 + te[6]) * 1000 + te[7];
        }
        else
        {
          //this might never show
          sts = 0; ets = 0;
        }
        elemidx++;
      break;
      default:
        //add text from index 512
        if (*ptp == 0x0D || *ptp == 0x0A)
        {
          elemidx = 1;
          //add subtitle element to list
          struct Subs *subs = (struct Subs *)malloc (sizeof (struct Subs));
          if (subs)
          {
            subs->idx = subidx;
            subs->smsts = sts;
            subs->emsts = ets;
            subs->text = strdup (subtext);
            subs->prev = NULL;
            subs->next = NULL;
            //
            if (!head)
              head = subs;
            else
            {
              subs->prev = node;
              node->next = subs;
            }
            node = subs;
            //
            //Nprintf ("add sub: >%s<\n", subs->text);
            ++subcnt;
          }
            //Nprintf ("next sub number %d\n", subcnt);
            stidx = 0;
        }
        else
        {
          stidx += snprintf (subtext + stidx, 510 - stidx, "%s\r\n", ptp);
            //Nprintf ("added %dB to %s\n", stidx, subtext);
        }
    }
  } /* while res game */
  Nprintf ("subs_load END processing %dsubs SRT '%s'\n", subcnt, path);
  //
  free (tmbuff);
  fclose (srtf);
  //
  return head;
}
