import subprocess
import sys

def generate_composite_view(class_file, output_file):
    try:
        xxd_output = subprocess.check_output(['xxd', class_file], text=True)
        javap_output = subprocess.check_output(['javap', '-verbose', class_file], text=True)
        with open(output_file, 'w') as out_file:
            out_file.write("Hex dump (xxd):\n")
            out_file.write("----------------\n")
            out_file.write(xxd_output)
            out_file.write("\n\njavap -verbose output:\n")
            out_file.write("----------------------\n")
            out_file.write(javap_output)
    except FileNotFoundError as e:
        print(f"Error: {e}. Ensure `xxd` and `javap` are installed and in your PATH.")
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {e}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python generate_composite_view.py <ClassName>")
        sys.exit(1)
    class_name = sys.argv[1]
    class_file = f"{class_name}.class"
    output_file = f"{class_name}-bytecode.txt"
    generate_composite_view(class_file, output_file)
    print(f"Composite view written to {output_file}")