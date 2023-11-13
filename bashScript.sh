#!/bin/bash

address_book_file="address_book.txt"

while true; do
    echo "Address Book Options:"
    echo "a) Create address book"
    echo "b) View address book"
    echo "c) Insert a record"
    echo "d) Delete a record"
    echo "e) Modify a record"
    echo "f) Exit"

    read -p "Enter your choice: " choice

    case "$choice" in
        a)
            touch "$address_book_file"
            echo "Address book created."
            ;;
        b)
            echo "Address Book Contents:"
            cat "$address_book_file"
            ;;
        c)
            read -p "Enter name: " name
            read -p "Enter address: " address
            echo "Name: $name, Address: $address" >> "$address_book_file"
            echo "Record inserted."
            ;;
        d)
            read -p "Enter name to delete: " delete_name
            sed -i "/$delete_name/d" "$address_book_file"
            echo "Record deleted."
            ;;
        e)
            read -p "Enter name to modify: " modify_name
            read -p "Enter new address: " new_address
            sed -i "s/$modify_name,.*/$modify_name, $new_address/" "$address_book_file"
            echo "Record modified."
            ;;
        f)
            echo "Exiting the address book program."
            exit 0
            ;;
        *)
            echo "Invalid option. Please choose a valid option (a-f)."
            ;;
    esac
done

