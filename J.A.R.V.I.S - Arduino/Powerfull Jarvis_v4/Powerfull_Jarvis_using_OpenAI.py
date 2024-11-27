import openai
from apikey import api_data
import pyttsx3
import speech_recognition as sr
import webbrowser
import requests
import datetime
import wikipedia
import random

# Assigning the OpenAI API key
openai.api_key = api_data

# Creating an instance of the OpenAI Completion object
completion = openai.Completion()

# Function to get AI-generated replies
def Reply(question):
    prompt = f'Chando: {question}\n Jarvis: '
    response = completion.create(prompt=prompt, engine="text-davinci-002", stop=['\Chando'], max_tokens=200)
    answer = response.choices[0].text.strip()
    return answer

# Initializing text-to-speech engine
engine = pyttsx3.init('sapi5')
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[0].id)

# Function to convert text to speech
def speak(text):
    engine.say(text)
    engine.runAndWait()

# Function to listen and convert speech to text
def takeCommand():
    r = sr.Recognizer()
    with sr.Microphone() as source:
        print('Listening....')
        r.pause_threshold = 1
        audio = r.listen(source)
    
    try:
        print("Recognizing.....")
        query = r.recognize_google(audio, language='en-in')
        print(f"Chando Said: {query} \n")
    except Exception as e:
        print("Say That Again....")
        return "None"
    return query

# Function to get the current weather of a city
def get_weather(city):
    api_key = "your_weather_api_key"  # Replace with your weather API key
    base_url = f"http://api.openweathermap.org/data/2.5/weather?q={city}&appid={api_key}&units=metric"
    response = requests.get(base_url)
    data = response.json()
    
    if data["cod"] != "404":
        main = data["main"]
        temperature = main["temp"]
        weather_desc = data["weather"][0]["description"]
        return f"The temperature in {city} is {temperature}°C with {weather_desc}."
    else:
        return "City not found."

# Function to get current time
def get_time():
    current_time = datetime.datetime.now().strftime("%I:%M %p")
    return f"The current time is {current_time}"

# Function to get a random joke
def tell_joke():
    jokes = [
        "Why don't skeletons fight each other? They don't have the guts.",
        "I told my wife she was drawing her eyebrows too high. She looked surprised.",
        "What do you call fake spaghetti? An impasta!"
    ]
    return random.choice(jokes)

# Main program execution
if __name__ == '__main__':
    speak("Hello! How can I assist you today?")
    
    while True:
        query = takeCommand().lower()
        
        if 'open youtube' in query:
            webbrowser.open("www.youtube.com")
            speak("Opening YouTube")
        
        elif 'open google' in query:
            webbrowser.open("www.google.com")
            speak("Opening Google")
        
        elif 'open github' in query:
            webbrowser.open("www.github.com")
            speak("Opening GitHub")
        
        elif 'time' in query:
            current_time = get_time()
            print(current_time)
            speak(current_time)
        
        elif 'weather' in query:
            speak("Please tell me the city name.")
            city = takeCommand().lower()
            weather = get_weather(city)
            print(weather)
            speak(weather)
        
        elif 'joke' in query:
            joke = tell_joke()
            print(joke)
            speak(joke)
        
        elif 'wikipedia' in query:
            speak("What would you like to know about?")
            search_query = takeCommand().lower()
            results = wikipedia.summary(search_query, sentences=2)
            print(results)
            speak(results)
        
        elif 'bye' in query:
            speak("Goodbye!")
            break
        
        else:
            # Default behavior is to pass the query to OpenAI for a response
            ans = Reply(query)
            print(ans)
            speak(ans)
