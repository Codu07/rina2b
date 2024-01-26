#!/usr/bin/env python3

class Agent(object):
  def __init__(self, name : str, config : dict):
    self._name = name

  def chat(self, message : str) -> str:
    return "I'm an AI agent, I can't chat yet!"


def build_agent():
  return Agent("test", {})