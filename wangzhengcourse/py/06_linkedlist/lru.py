class DListNode(object):
    def __init__(self, x, y):
        self.key = x
        self.val = y
        self.next = None
        self.prev = None

class LRU_cache:
    def __init__(self, capacity: int):
        self.cap = capacity
        self.hkeys = {}
        self.top = DListNode(None, -1)
        self.tail = DListNode(None, -1)
        self.top.next = self.tail
        self.tail.prev = self.top

    def get(self, key: int) -> int:

        if key in self.hkeys.keys():
            # 更新结点顺序
            cur = self.hkeys[key]
            # 跳出原位置
            cur.next.prev = cur.prev
            cur.prev.next = cur.next
            # 最近用过的置于链表首部
            top_node = self.top.next
            self.top.next = cur
            cur.prev = self.top
            cur.next = top_node
            top_node.prev = cur

            return self.hkeys[key].val
        return -1

    def put(self, key: int, value:int) -> None:
        if key in self.hkeys.keys():
            cur = self.hkeys[key]
            cur.val = value

            cur.next.prev = cur.prev
            cur.prev.next = cur.next

            top_Node = self.top.next
            self.top.next = cur
            cur.prev = self.top
            cur.next = top_Node
            top_Node.prev = cur
        else:
            cur = DListNode(key, value)
            self.hkeys[key] = cur

            top_Node = self.top.next
            self.top.next = cur
            cur.prev = self.top
            cur.next = top_Node
            top_Node.prev = cur

            if len(self.hkeys) > self.cap: 
                last = self.tail.prev

                self.hkeys.pop(last.key)
                last.prev.next = self.tail
                self.tail.prev = last.prev

    def __repr__(self):
        vals = []
        p = self.top.next
        while p.next:
            vals.append(str(p.val))
            p = p.next
        return '->'.join(vals)


if __name__ == "__main__":
    cache = LRU_cache(2)
    cache.put(1, 1)
    cache.put(2, 2)
    print(cache)
    cache.get(1)  
    cache.put(3, 3)  
    print(cache)
    cache.get(2)  
    cache.put(4, 4)  
    print(cache)
    cache.get(1) 
    cache.get(3)  
    print(cache)
    cache.get(4)  
    print(cache)


