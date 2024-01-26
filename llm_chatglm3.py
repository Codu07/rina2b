from llm import LLM

class ChatGLM3(LLM):
  def __init__(self, config: dict) -> None:
    super().__init__(config)

  def chat(self, prompt: str, functions: dict, history: list, options: {}) -> str:
    return super().chat(prompt, functions, history)
