from llm import LLM
from llm import LLMManager


class Agent(object):
  def __init__(self, name : str, config : dict):
    self._name = name

  def chat(self, message : str) -> str:
    return "I'm an AI agent, I can't chat yet!"


def build_agent(name : str, llms : LLM, config : dict):
  return Agent("test", {})