class TravelDocument:
    def __init__(self, name, doc_id, nationality):
        self.name = name
        self.doc_id = doc_id
        self.nationality = nationality

class DocumentVerificationSystem:
    def __init__(self):
        self.documents = []
        self.filename = "documents.txt"
        self.load_documents_from_file()

    def create_document(self, name, doc_id, nationality):
        document = TravelDocument(name, doc_id, nationality)
        self.documents.append(document)
        self.save_documents_to_file()
        print("Document created successfully!")

    def read_document(self, doc_id):
        for document in self.documents:
            if document.doc_id == doc_id:
                print(f"Name: {document.name}")
                print(f"Document Number: {document.doc_id}")
                print(f"Nationality: {document.nationality}")
                return
        print("Document not found!")

    def verify_document(self, doc_id, nationality):
        for document in self.documents:
            if document.doc_id == doc_id and document.nationality == nationality:
                print("Document Verified Successfully!")
                print("Holder Name:", document.name)
                print("Nationality:", document.nationality)
                return
        print("Document not found or nationality mismatch!")

    def update_document(self, doc_id, name=None, nationality=None):
        for document in self.documents:
            if document.doc_id == doc_id:
                if name:
                    document.name = name
                if nationality:
                    document.nationality = nationality
                self.save_documents_to_file()
                print("Document updated successfully!")
                return
        print("Document not found!")

    def delete_document(self, doc_id):
        for document in self.documents:
            if document.doc_id == doc_id:
                self.documents.remove(document)
                self.save_documents_to_file()
                print("Document deleted successfully!")
                return
        print("Document not found!")

    def load_documents_from_file(self):
        try:
            with open(self.filename, 'r') as file:
                for line in file:
                    data = line.strip().split(',')
                    name, doc_id, nationality = data
                    self.documents.append(TravelDocument(name, doc_id, nationality))
            print("Documents loaded successfully from file!")
        except FileNotFoundError:
            print("File not found!")

    def save_documents_to_file(self):
        try:
            with open(self.filename, 'w') as file:
                for document in self.documents:
                    file.write(f"{document.name},{document.doc_id},{document.nationality}\n")
            print("Documents saved successfully to file!")
        except Exception as e:
            print(f"Error occurred while saving documents: {e}")

def main():
    system = DocumentVerificationSystem()

    while True:
        print("\n===== Travel Document Verification System =====")
        print("1. Create Document")
        print("2. Read Document")
        print("3. Verify Document")
        print("4. Update Document")
        print("5. Delete Document")
        print("6. Exit")

        choice = input("Enter your choice: ")

        if choice == '1':
            name = input("Enter name: ")
            doc_id = input("Enter document number: ")
            nationality = input("Enter nationality: ")
            system.create_document(name, doc_id, nationality)

        elif choice == '2':
            doc_id = input("Enter document number to read: ")
            system.read_document(doc_id)

        elif choice == '3':
            doc_id = input("Enter document number for verification: ")
            nationality = input("Enter nationality: ")
            system.verify_document(doc_id, nationality)

        elif choice == '4':
            doc_id = input("Enter document number to update: ")
            name = input("Enter updated name (leave blank to skip): ")
            nationality = input("Enter updated nationality (leave blank to skip): ")
            system.update_document(doc_id, name, nationality)

        elif choice == '5':
            doc_id = input("Enter document number to delete: ")
            system.delete_document(doc_id)

        elif choice == '6':
            print("Exiting...")
            break

        else:
            print("Invalid choice! Please enter a valid option.")
    main()
