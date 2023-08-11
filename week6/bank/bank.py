def main():
    # getting input
    phrase = input("Greeting: ")
    text = phrase.lower().strip().split()

    if "hello" in text or "hello," in text:
        print("$0")
    elif text[0][0] == 'h':
        print("$20")
    else:
        print("$100")


if __name__ == "__main__":
    main()