#ifndef	_JRB_H_
#define	_JRB_H_

#include "jval.h"

/** Main jrb_node.  Bạn chỉ sử dụng các trường
    flink
    blink
    k.key or k.ikey
    v.val
 */


typedef struct jrb_node {
  unsigned char red;
  unsigned char internal;
  unsigned char left;
  unsigned char roothead;  /**< Bit 1 là gốc. Bit 2 là đầu*/
  struct jrb_node *flink;
  struct jrb_node *blink;
  struct jrb_node *parent;
  Jval key;
  Jval val;
} *JRB;

/** Creates a new rb-tree. */
extern JRB make_jrb();


/** Tạo một nút với key key và val val và chèn nó vào cây.
 *  jrb_insert sử dụng strcmp () làm chức năng so sánh.  jrb_inserti uses <>=,
 *  jrb_insertg uses func()
 */

extern JRB jrb_insert_str(JRB tree, char *key, Jval val);
extern JRB jrb_insert_int(JRB tree, int ikey, Jval val);
extern JRB jrb_insert_dbl(JRB tree, double dkey, Jval val);
extern JRB jrb_insert_gen(JRB tree, Jval key, Jval val, int (*func)(Jval,Jval));

/* Trả về một nút bên ngoài trong t có giá trị bằng k. Trả về NULL nếu
 * không có node như vậy trong cây.
 */

extern JRB jrb_find_str(JRB root, char *key);
extern JRB jrb_find_int(JRB root, int ikey);
extern JRB jrb_find_dbl(JRB root, double dkey);
extern JRB jrb_find_gen(JRB root, Jval, int (*func)(Jval, Jval));


/** Trả về  một node bên ngòai trong t có gia trị bằng 
 * k hoặc giá trị của nó là giá trị nhỏ nhất lơn hơn k. Sets found to
 * 1 if the key was found, and 0 otherwise.
 */

extern JRB jrb_find_gte_str(JRB root, char *key, int *found);
extern JRB jrb_find_gte_int(JRB root, int ikey, int *found);
extern JRB jrb_find_gte_dbl(JRB root, double dkey, int *found);
extern JRB jrb_find_gte_gen(JRB root, Jval key, 
                              int (*func)(Jval, Jval), int *found);


/** Tạo một nút với key key và val val và chèn nó vào  
 *  cây trước / sau node nd.  Không kiểm tra để đảm bảo rằng bạn  
 *  đang giữ đúng thứ tự.
 */

/** Deletes and free(3) a node but not the key or val. Xóa node*/
extern void jrb_delete_node(JRB node);

/** Deletes and free(3) an entire tree. Xóa cây*/
extern void jrb_free_tree(JRB root);

/** Returns node->v.val -- this is to shut lint up. */
extern Jval jrb_val(JRB node);

/** Returns # of black nodes in path from n to the root. */
extern int jrb_nblack(JRB n);

/** Returns # of nodes in path from n to the root. */
int jrb_plength(JRB n);

/** Convenience macros */
#define jrb_first(n) (n->flink)
#define jrb_last(n) (n->blink)
#define jrb_next(n) (n->flink)
#define jrb_prev(n) (n->blink)
#define jrb_empty(t) (t->flink == t)
#ifndef jrb_nil
#define jrb_nil(t) (t)
#endif
 
#define jrb_traverse(ptr, lst) \
  for(ptr = jrb_first(lst); ptr != jrb_nil(lst); ptr = jrb_next(ptr))
 
#define jrb_rtraverse(ptr, lst) \
  for(ptr = jrb_last(lst); ptr != jrb_nil(lst); ptr = jrb_prev(ptr))
 
#endif
