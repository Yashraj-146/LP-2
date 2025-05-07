from sentence_transformers import SentenceTransformer, util
import torch
import streamlit as st

# Load model once
@st.cache_resource
def load_model():
    return SentenceTransformer('paraphrase-MiniLM-L6-v2')

model = load_model()

# FAQ knowledge base
faq_pairs = {
    "What is your name?": "I'm a customer support assistant.",
    "Do you offer refunds?": "Yes, we offer refunds within 30 days of purchase.",
    "Tell me about the product.": "Can you specify which product you're interested in?",
    "What is the price of the product?": "Please mention the product name for pricing details.",
    "Hello": "Hi there! How can I assist you today?",
    "What is my name?": "You are Yashraj, student of PICT, Pune.",
    "Thank you": "You're welcome!",
    "Bye": "Goodbye! Have a great day.",
    "CEO": "Which company's CEO you want to know about?",
    "Apple": "Apple's CEO is Tim Cook.",
    "Tesla": "Tesla's CEO is Elon Musk.",
    "How can I track my order?": "You can track your order using the tracking link sent to your email after purchase.",
    "Can I cancel my order?": "Yes, you can cancel your order within 24 hours of placing it.",
    "What payment methods do you accept?": "We accept credit/debit cards, UPI, PayPal, and net banking.",
    "Do you ship internationally?": "Yes, we offer international shipping to most countries.",
    "How long does delivery take?": "Delivery typically takes 3-7 business days depending on your location.",
    "Is there any warranty on the product?": "Yes, our products come with a 1-year warranty.",
    "I forgot my password.": "You can reset your password using the 'Forgot Password' link on the login page.",
    "Can I change my shipping address?": "Yes, please contact support within 12 hours of placing the order to change your address.",
}

# Encode questions once
questions = list(faq_pairs.keys())
question_embeddings = model.encode(questions, convert_to_tensor=True)

def get_response(user_input):
    user_embedding = model.encode(user_input, convert_to_tensor=True)
    cosine_scores = util.pytorch_cos_sim(user_embedding, question_embeddings)
    top_result = torch.argmax(cosine_scores)

    if cosine_scores[0][top_result] > 0.6:
        return faq_pairs[questions[top_result]]
    else:
        return "I'm sorry, I didn't understand that. Could you please rephrase?"

# Initialize chat history
if "messages" not in st.session_state:
    st.session_state.messages = []

st.title("🧠 NLP Chatbot (BERT-powered)")

# Display chat history
for msg in st.session_state.messages:
    with st.chat_message(msg["role"]):
        st.markdown(msg["content"])

# Chat input
user_input = st.chat_input("Ask a question...")

if user_input:
    # Display user message
    st.session_state.messages.append({"role": "user", "content": user_input})
    with st.chat_message("user"):
        st.markdown(user_input)

    # Get bot response
    response = get_response(user_input)
    st.session_state.messages.append({"role": "assistant", "content": response})
    with st.chat_message("assistant"):
        st.markdown(response)
