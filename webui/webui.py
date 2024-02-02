import streamlit as st


st.title("🚀 Rina2B")


if 'messages' not in st.session_state:
  st.session_state.messages = []

for msg in st.session_state.messages:
    st.chat_message(msg["role"]).write(msg["content"])

if prompt := st.chat_input():
  st.session_state.messages.append({"role": "user", "content": prompt})
  st.chat_message("user").write(prompt)