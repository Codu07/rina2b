

class ShorttermMemory(object):
  def __init__(self):
    self.memory = {}


class LongtermMemory(object):
  def __init__(self):
    self.memory = {}

  def append(self, key, value):
    if key in self.memory:
      self.memory[key].append(value)
    else:
      self.memory[key] = [value]


class Memory(object):
  def __init__(self):
    self.shortterm = ShorttermMemory()
    self.longterm = LongtermMemory()

  def update_shortterm(self, key, value):
    self.shortterm.memory[key] = value

  def update_longterm(self, key, value):
    self.longterm.memory[key] = value

