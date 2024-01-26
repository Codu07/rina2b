import io
import yaml
from agent import Agent
from memory import Memory
from llm import LLM
from llm import build_llm

class Rina(object):
  def __init__(self, config_path: str):
    with io.open(config_path, 'r', encoding='utf-8') as stream:
      self._config = yaml.load(stream, Loader=yaml.FullLoader)
    print('config:')
    print(self._config)
    self._llm = None
    self._memory = None
    self._agent = None
    self.__init_from_config(self._config)
    return

  def chat(self, message: str):
    return {"rina": "Greetings, human!"}

  def say_hello(self):
    print("Hello, Rina!")

  def __init_from_config(self, config: dict):
    llm_config = config['llm']
    self.__init_llm_from_config(llm_config)

    memory_config = config['memory']
    self.__init_memory_from_config(memory_config)

    agent_config = config['agent']
    self.__init_agent_from_config(self._llm, self._memory, agent_config)
    return  

  def __init_llm_from_config(self, llm_config: list):
    for item in llm_config:
      name = item['name']
      type = item['type']
      llm = build_llm(type, item)
    
    self._llm = build_llm(type, llm_config)
    return
  
  def __init_memory_from_config(self, memory_config: dict):
    return

  def __init_agent_from_config(self, llm: LLM, memory: Memory, agent_config: dict):
    return


