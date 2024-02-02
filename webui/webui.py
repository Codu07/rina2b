import streamlit as st
import requests


st.title("🚀 Rina2B")


if 'sid' not in st.session_state:
  st.session_state.sid = ""

if 'messages' not in st.session_state:
  st.session_state.messages = []

sid = st.session_state.sid

for msg in st.session_state.messages:
    st.chat_message(msg["role"]).write(msg["content"])

if prompt := st.chat_input():
  st.session_state.messages.append({"role": "user", "content": prompt})
  st.chat_message("user").write(prompt)
  response = requests.post("http://localhost:8087/api/chat", json={"sid": sid, "message": prompt}).json()
  st.session_state.messages.append({"role": "assistant", "content": response["message"]})
  st.session_state.sid = response["sid"]
  st.chat_message("assistant").write(response["message"])
  print(response)