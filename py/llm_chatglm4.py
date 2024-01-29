from llm import LLM

class ChatGLM4(LLM):
  def __init__(self, config: dict):
    super.__init__(config)

  def chat(self, prompt: str, functions: dict, history: list, options: dict) -> str:
    return super().chat(prompt, functions, history, options)