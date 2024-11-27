import pyttsx3 
import speech_recognition as sr 
import datetime
import os
import webbrowser
import requests
import wikipedia
import json
import random
import pyautogui
import time

# Initialize the speech engine
engine = pyttsx3.init('sapi5')
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[0].id)

def speak(audio):
    engine.say(audio)
    engine.runAndWait()

def wishMe():
    hour = int(datetime.datetime.now().hour)
    if hour >= 0 and hour < 12:
        speak("Good Morning, Mr Stark")
    elif hour >= 12 and hour < 18:
        speak("Good Afternoon, Mr Stark")   
    else:
        speak("Good Evening, Mr Stark")  
    speak("All systems are operational. How can I assist you?")       

def takeCommand():
    r = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening...")
        r.pause_threshold = 1
        audio = r.listen(source)
    try:
        print("Recognizing...")    
        query = r.recognize_google(audio, language='en-in')
        print(f"User said: {query}\n")
    except Exception as e:
        print("Say that again please...")  
        return "None"
    return query

def getWeather():
    api_key = "b1d78c100d76b23b6b73c8a08b9cc2d0"  # Replace with your OpenWeatherMap API key
    base_url = "http://api.openweathermap.org/data/2.5/weather?"
    city_name = "Kolkata"  # Replace with your city name
    complete_url = base_url + "appid=" + api_key + "&q=" + city_name
    
    response = requests.get(complete_url)
    x = response.json()
    
    print(json.dumps(x, indent=4))  # Print the JSON response for debugging
    
    if x["cod"] != "404":
        if "main" in x and "weather" in x:
            y = x["main"]
            current_temperature = y["temp"]
            current_pressure = y["pressure"]
            current_humidity = y["humidity"]
            z = x["weather"]
            weather_description = z[0]["description"]
            
            speak(f"The temperature is {current_temperature - 273.15:.2f} degree Celsius, "
                  f"pressure is {current_pressure} hPa, humidity is {current_humidity} percent, "
                  f"and the weather description is {weather_description}.")
        else:
            speak("Weather information is incomplete, please try again later.")
    else:
        speak("City Not Found")

def tellJoke():
    jokes = [
        "Why don't scientists trust atoms? Because they make up everything!",
        "How does a penguin build its house? Igloos it together.",
        "Why did the scarecrow win an award? Because he was outstanding in his field."
    ]
    speak(random.choice(jokes))

def setReminder():
    speak("What would you like me to remind you about?")
    reminder = takeCommand()
    if reminder == "None" or reminder.strip() == "":
        speak("I couldn't understand the reminder. Please try again.")
        return
    
    speak(f"Setting a reminder for: {reminder}")
    with open("reminders.txt", "a") as f:
        f.write(reminder + "\n")
    speak("Reminder has been set.")

def listReminders():
    try:
        with open("reminders.txt", "r") as f:
            reminders = f.readlines()
        if not reminders:
            speak("You have no reminders.")
        else:
            speak("Here are your reminders:")
            for reminder in reminders:
                speak(reminder.strip())
    except FileNotFoundError:
        speak("You have no reminders.")

def closeTab():
    speak("Closing the current tab")
    pyautogui.hotkey('ctrl', 'w')

def searchGoogle():
    speak("What would you like to search for?")
    query = takeCommand()
    if query == "None" or query.strip() == "":
        speak("I couldn't understand the search query. Please try again.")
        return
    
    speak(f"Searching Google for: {query}")
    webbrowser.open(f"https://www.google.com/search?q={query}")

# Update the main loop to handle Google search
if __name__ == "__main__":
    wishMe()
    while True:
        query = takeCommand().lower()

        if 'hello' in query:
            speak('Yes boss')
        
        elif 'play music' in query:
            music_dir = "D:\\Audio\\SUBRATA"
            songs = os.listdir(music_dir)
            print(songs)    
            os.startfile(os.path.join(music_dir, songs[0]))

        elif 'the time' in query:
            strTime = datetime.datetime.now().strftime("%H:%M:%S")    
            speak(f"Sir, the time is {strTime}")

        elif 'open code' in query:
            codePath = ""
            os.startfile(codePath)
        
        elif 'weather' in query:
            getWeather()
        
        elif 'wikipedia' in query:
            speak('Searching Wikipedia...')
            query = query.replace("wikipedia", "")
            results = wikipedia.summary(query, sentences=2)
            speak("According to Wikipedia")
            speak(results)

        elif 'open youtube' in query:
            webbrowser.open("youtube.com")
            speak("opening YouTube")

        elif 'open google' in query:
            webbrowser.open("google.com")
            speak("opening google")

        elif 'set reminder' in query:
            setReminder()

        elif 'list reminders' in query:
            listReminders()

        elif 'tell me a joke' in query:
            tellJoke()

        elif 'close tab' in query:
            closeTab()

        elif 'search in google' in query:
            searchGoogle()

        elif 'wake up' in query:
            speak("yes boss tell me how can i halp you ?")

        elif 'exit' in query:
            speak('Boss, have a good day. Take care of yourself.')
            break
