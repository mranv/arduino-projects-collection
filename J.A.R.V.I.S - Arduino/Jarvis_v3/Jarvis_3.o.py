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
import subprocess
import smtplib
from email.mime.text import MIMEText
import psutil

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

def openCalculator():
    speak("Opening Calculator")
    subprocess.Popen('calc.exe')

def closeCalculator():
    speak("Closing Calculator")
    os.system("taskkill /f /im Calculator.exe")

def openCamera():
    speak("Opening Camera")
    subprocess.Popen('start microsoft.windows.camera:', shell=True)

def closeCamera():
    speak("Closing Camera")
    os.system("taskkill /f /im WindowsCamera.exe")

def getNews():
    api_key = "your_newsapi_key"  # Replace with your NewsAPI key
    url = f"http://newsapi.org/v2/top-headlines?country=in&apiKey={api_key}"
    response = requests.get(url)
    news_data = response.json()
    
    if news_data["status"] == "ok":
        speak("Here are the top news headlines:")
        for i, article in enumerate(news_data["articles"][:5], 1):
            speak(f"News {i}: {article['title']}")
    else:
        speak("Sorry, I couldn't fetch the news at the moment.")

def getSystemInfo():
    cpu_usage = psutil.cpu_percent(interval=1)
    memory_info = psutil.virtual_memory()
    disk_info = psutil.disk_usage('/')
    
    speak(f"CPU usage is at {cpu_usage} percent.")
    speak(f"Memory usage is at {memory_info.percent} percent.")
    speak(f"Disk usage is at {disk_info.percent} percent.")

def sendEmail(to, subject, body):
    speak("Sending email...")
    sender_email = "your_email@example.com"
    sender_password = "your_password"
    
    msg = MIMEText(body)
    msg['Subject'] = subject
    msg['From'] = sender_email
    msg['To'] = to

    try:
        with smtplib.SMTP_SSL('smtp.gmail.com', 465) as server:
            server.login(sender_email, sender_password)
            server.sendmail(sender_email, to, msg.as_string())
        speak("Email has been sent successfully.")
    except Exception as e:
        speak("Failed to send the email.")
        print(e)

def setAlarm(alarm_time):
    speak(f"Setting an alarm for {alarm_time}.")
    while True:
        current_time = datetime.datetime.now().strftime("%H:%M")
        if current_time == alarm_time:
            speak("Wake up! It's time!")
            break
        time.sleep(30)

def increaseVolume():
    pyautogui.press('volumeup')
    speak("Volume increased")

def decreaseVolume():
    pyautogui.press('volumedown')
    speak("Volume decreased")

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
            codePath = "path_to_your_code_editor"  # Specify your code editor's path
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

        elif 'open calculator' in query:
            openCalculator()

        elif 'close calculator' in query:
            closeCalculator()

        elif 'open camera' in query:
            openCamera()

        elif 'close camera' in query:
            closeCamera()

        elif 'news' in query:
            getNews()

        elif 'system info' in query:
            getSystemInfo()

        elif 'send email' in query:
            speak("Who should I send the email to?")
            recipient = takeCommand().lower()
            speak("What should be the subject?")
            subject = takeCommand()
            speak("What should I say?")
            body = takeCommand()
            sendEmail(recipient, subject, body)

        elif 'set alarm' in query:
            speak("At what time? Please say the time in 24-hour format, for example 18:30.")
            alarm_time = takeCommand()
            setAlarm(alarm_time)

        elif 'increase volume' in query:
            increaseVolume()

        elif 'decrease volume' in query:
            decreaseVolume()

        elif 'quit' in query or 'exit' in query:
            speak("Goodbye Mr Stark!")
            break
