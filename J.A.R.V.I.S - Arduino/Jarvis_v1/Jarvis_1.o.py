import speech_recognition as sr
import pyttsx3
import datetime
import wikipedia
import os

# Initialize text-to-speech engine
engine = pyttsx3.init()
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[1].id)  # Change to voices[0].id for a male voice

# Function for speech output
def speak(text):
    engine.say(text)
    engine.runAndWait()

# Function to listen to the user's voice command
def take_command():
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
    return query.lower()

# Greeting function
def greet_user():
    hour = int(datetime.datetime.now().hour)
    if hour >= 0 and hour < 12:
        speak("Good morning!")
    elif hour >= 12 and hour < 18:
        speak("Good afternoon!")
    else:
        speak("Good evening!")
    speak("I am Jarvis. How can I assist you?")

# Main logic
if __name__ == "__main__":
    greet_user()
    while True:
        command = take_command()

        # Task 1: Open a file or program (example: Notepad)
        if "open notepad" in command:
            speak("Opening Notepad")
            os.system("notepad")

        # Task 2: Get information from Wikipedia
        elif "wikipedia" in command:
            speak("Searching Wikipedia...")
            command = command.replace("wikipedia", "")
            try:
                result = wikipedia.summary(command, sentences=2)
                speak("According to Wikipedia")
                speak(result)
            except wikipedia.exceptions.DisambiguationError as e:
                speak("There are multiple results. Please be more specific.")

        # Task 3: Get the time
        elif "time" in command:
            current_time = datetime.datetime.now().strftime("%H:%M:%S")
            speak(f"The time is {current_time}")

        # Task 4: Close the assistant
        elif "stop" in command or "exit" in command:
            speak("Goodbye!")
            break

        # Task 5: Handle unrecognized command
        else:
            speak("I didn't understand that command. Please try again.")
