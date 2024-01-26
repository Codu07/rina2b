class LLM(object):
  def __init__(self, config: dict) -> None:
    pass

  def chat(self, prompt: str, functions: dict, history: list) -> str:
    raise NotImplementedError()

 
class LLMManager(object):
  def __init__(self) -> None:
    self._llms = {}
    pass

  def register_llm(self, name: str, llm: LLM):
    self._llms[name] = llm

  def get_llm(self, name: str) -> LLM:
    return self._llms.get(name, None)


def build_llm(type: str, config: dict) -> LLM:
  from llm_chatglm3 import ChatGLM3
  if type == 'chatglm3':
    return ChatGLM3(config)
  else:
    raise ValueError(f'Unsupported LLM type: {type}')

