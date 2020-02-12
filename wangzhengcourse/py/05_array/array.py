class Array(object):
    def __init__(self, size):
        self.size = size
        self.len  = 0
        self.i = 0
        self.data = []

    def __str__(self):
        return 'Class Array'

    def __repr__(self):
        return str(self.data)

    def __getitem__(self, idx: int):
        if idx < self.len:
            return self.data[idx]
    
    def __setitem__(self, idx: int, val: int):
        if idx < self.len:
            self.data[idx] = val

    def __len__(self):
        return self.len

    def __iter__(self):
        self.i = 0
        return self

    def __next__(self):
        if self.i == self.len:
            raise StopIteration
        val = self.data[self.i]
        self.i += 1
        return val

    def insert(self, idx: int, val: int):
        if idx < self.size:
            self.data.insert(idx, val)
            self.len += 1

    def find(self, val: int):
        for i in range(self.len):
            if self.data[i] == val:
                return i
        return -1

    def delete(self, idx: int):
        if idx < self.len and idx >= 0:
            self.data.pop(idx)
            self.len -= 1


def test():
    array = Array(5)
    array.insert(0, 3)
    array.insert(0, 4)
    array.insert(1, 5)
    array.insert(3, 9)
    array.insert(3, 10)
    print(array)
    array.delete(2)
    print(len(array), array[2], array.find(10))
    print([s for s in array])


if __name__ == "__main__":
    test()