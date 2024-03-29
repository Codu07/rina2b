from fastapi import FastAPI
from pydantic import BaseModel
from rina import Rina


class Message(BaseModel):
  content: str

app = FastAPI()
rina = Rina('./rina.yaml')

@app.get("/")
def get_index():
  return {"rina2b": "Hello"}

@app.get("/health")
def get_health():
  return {"status": "ok"}

@app.post("/rina/chat")
def post_rina_chat(message: Message):
  return rina.chat(message.content)