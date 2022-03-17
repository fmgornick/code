#!/usr/bin/env python3

import socket
import os
import stat
from urllib.parse import unquote_plus

from threading import Thread

# Equivalent to CRLF, named NEWLINE for clarity
NEWLINE = "\r\n"
OK = "HTTP/1.1 200 OK{}Connection: close{}{}".format(NEWLINE, NEWLINE, NEWLINE)
NOT_FOUND = "HTTP/1.1 404 NOT FOUND{}Connection: close{}{}".format(NEWLINE, NEWLINE, NEWLINE)
FORBIDDEN = "HTTP/1.1 403 FORBIDDEN{}Connection: close{}{}".format(NEWLINE, NEWLINE, NEWLINE)
REDIRECT = "HTTP/1.1 307 (Temporary Redirect){}Connection: close{}{}".format(NEWLINE, NEWLINE, NEWLINE)


# Let's define some functions to help us deal with files, since reading them
# and returning their data is going to be a very common operation.

def get_file_contents(file_name):
    """Returns the text content of `file_name`"""
    with open(file_name, "r") as f:
        return f.read()


def get_file_binary_contents(file_name):
    """Returns the binary content of `file_name`"""
    with open(file_name, "rb") as f:
        return f.read()


def has_permission_other(file_name):
    """Returns `True` if the `file_name` has read permission on other group

    In Unix based architectures, permissions are divided into three groups:

    1. Owner
    2. Group
    3. Other

    When someone requests a file, we want to verify that we've allowed
    non-owners (and non group) people to read it before sending the data over.
    """
    stmode = os.stat(file_name).st_mode
    return getattr(stat, "S_IROTH") & stmode > 0


# Some files should be read in plain text, whereas others should be read
# as binary. To maintain a mapping from file types to their expected form, we
# have a `set` that maintains membership of file extensions expected in binary.
# We've defined a starting point for this set, which you may add to as
# necessary.
# TODO: Finish this set with all relevant files types that should be read in
# binary
binary_type_files = set(["jpg", "jpeg", "png", "mp3"])


def should_return_binary(file_extension):
    """
    Returns `True` if the file with `file_extension` should be sent back as
    binary.
    """
    return file_extension in binary_type_files


# For a client to know what sort of file you're returning, it must have what's
# called a MIME type. We will maintain a `dictionary` mapping file extensions
# to their MIME type so that we may easily access the correct type when
# responding to requests.
# TODO: Finish this dictionary with all required MIME types
mime_types = {
    "html": "text/html",
    "css": "text/css",
    "js": "text/javascript",
    "mp3": "audio/mpeg",
    "png": "image/png",
    "jpg": "image/jpeg",
    "jpeg": "image/jpeg"
}


# array of possible locations for our files
paths = ["../html/", "../css/", "../js/", "../img/"]


def get_file_mime_type(file_extension):
    """
    Returns the MIME type for `file_extension` if present, otherwise
    returns the MIME type for plain text.
    """
    mime_type = mime_types[file_extension]
    return mime_type if mime_type is not None else "text/plain"


class HTTPServer:
    """
    Our actual HTTP server which will service GET and POST requests.
    """

    def __init__(self, host="localhost", port=9001, directory="."):
        print(f"Server started. Listening at http://{host}:{port}/")
        self.host = host
        self.port = port
        self.working_dir = directory

        self.setup_socket()
        self.accept()

        self.teardown_socket()

    def setup_socket(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.bind((self.host, self.port))
        self.sock.listen(128)

    def teardown_socket(self):
        if self.sock is not None:
            self.sock.shutdown(1) # might not be 1
            self.sock.close()

    def accept(self):
        while True:
            (client, address) = self.sock.accept()
            th = Thread(target=self.accept_request, args=(client, address))
            th.start()

    def accept_request(self, client_sock, client_addr):
        data = client_sock.recv(4096)
        req = data.decode("utf-8")

        response = self.process_response(req)
        client_sock.send(response)

        # clean up
        client_sock.shutdown(1)
        client_sock.close()

    def process_response(self, request):
        formatted_data = request.strip().split(NEWLINE)
        request_words = formatted_data[0].split()

        if len(request_words) == 0:
            return

        requested_file = request_words[1][1:]
        # add a head request
        if request_words[0] == "HEAD":
            return self.head_request(requested_file, formatted_data)
        if request_words[0] == "GET":
            return self.get_request(requested_file, formatted_data)
        if request_words[0] == "POST":
            return self.post_request(requested_file, formatted_data)
        return self.method_not_allowed()

    # NOT REQUIRED: head request response method
    def head_request(self, requested_file, data):
        if not os.path.exists(requested_file):
            response = NOT_FOUND
        elif not has_permission_other(requested_file):
            response = FORBIDDEN
        else:
            response = OK
        return response.encode('utf-8')

    # TODO: Write the response to a GET request
    def get_request(self, requested_file, data):
        """
        Responds to a GET request with the associated bytes.
        
        If the request is to redirect to a url (first item in URI),
        responds with a redirect request with HTTP 307 (Temporary Redirect)
        status code and a location header
        
        If the request is to a file that does not exist, returns
        a `NOT FOUND` error.

        If the request is to a file that does not have the `other`
        read permission, returns a `FORBIDDEN` error.

        Otherwise, we must read the requested file's content, either
        in binary or text depending on `should_return_binary` and
        send it back with a status set and appropriate mime type
        depending on `get_file_mime_type`.
        """

        # if the GET request contains a redirect, respond with the new location 
        # containing the query string
        if "redirect" in requested_file:
            loc = requested_file.split("=",1)[-1]
            return self.temporary_redirect(loc)

        # check if file exists in any of the paths available
        for i in paths:
            # append relative path to requested file
            file_path = requested_file.split('/')[-1]
            file_path = i + file_path
            # if the path is valid, then either 200 or 403
            if os.path.exists(file_path):
                # if permissions don't allow access then return 403
                if not has_permission_other(file_path):
                    return self.resource_forbidden()

                # if everything works fine, return a 200 with file contents
                else:
                    return self.resource_ok(file_path)

        """
        if path doesn't exist, return 404
        """
        return self.resource_not_found()


    # TODO: Write the response to a POST request
    def post_request(self, requested_file, data):
        """
        Responds to a POST request with an HTML page with keys and values
        echoed per the requirements writeup.

        A post request through the form will send over key value pairs
        through "x-www-form-urlencoded" format. You may learn more about
        that here:
          https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/POST
        You /do not/ need to check the POST request's Content-Type to
        verify the encoding used (although a real server would).

        From the request, each key and value should be extracted. A row in
        the HTML table will hold a single key-value pair. With the key having
        the first column and the value the second. If a request sent n
        key-value pairs, the HTML page returned should contain a table like:

        | key 1 | val 1 |
        | key 2 | val 2 |
        | ...   | ...   |
        | key n | val n |

        Care should be taken in forming values with spaces. Since the request
        was urlencoded, it will need to be decoded using
        `urllib.parse.unquote`.
        """
        # get query string from POST request
        query = data[-1].split('&')
        # parse query string into dictionary
        dict = {x[0] : x[1] for x in [x.split("=") for x in query ]}
        for k,y in dict.items():
            # use unquote function to turn URL string into readable ascii
            dict[k] = unquote_plus(y)

        # start of HTML file for POST response
        body = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><link rel=\"stylesheet\" type=\"text/css\" href=\"MyForm.css\"><title>Form Submission</title></head><table id=\"form_table\">"

        # end of html file
        end = "</table></body></html>"

        # add table elements to HTML file
        for k,y in dict.items():
            row = "<tr><td>{}</td><td>{}</td></tr>".format(k,y)
            body += row
        # finish off HTML file
        body += end

        builder = ResponseBuilder()
        # response status
        builder.set_status("200", "OK")
        # set content type equal to html
        builder.add_header("Content-Type", mime_types["html"])
        builder.add_header("Connection", "close")
        # put HTML file in the body of our response
        builder.set_content(body)
        return builder.build()

    def method_not_allowed(self):
        """
        Returns 405 not allowed status and gives allowed methods.

        TODO: If you are not going to complete the `ResponseBuilder`,
        This must be rewritten.
        """
        builder = ResponseBuilder()
        builder.set_status("405", "METHOD NOT ALLOWED")
        allowed = ", ".join(["GET", "POST"])
        builder.add_header("Allow", allowed)
        builder.add_header("Connection", "close")
        return builder.build()

    # for 307
    def temporary_redirect(self, loc):
        builder = ResponseBuilder()
        # response status
        builder.set_status("307", "(Temporary Redirect)")
        builder.set_location(loc)
        builder.add_header("Connection", "close")
        return builder.build()

    # for 404
    def resource_not_found(self):
        """
        Returns 404 not found status and sends back our 404.html page.
        """
        builder = ResponseBuilder()
        # response status
        builder.set_status("404", "NOT FOUND")
        builder.add_header("Connection", "close")
        # return 404 html page in contents
        builder.set_content(get_file_contents("../html/404.html"))
        return builder.build()

    # for 403
    def resource_forbidden(self):
        """
        Returns 403 FORBIDDEN status and sends back our 403.html page.
        """
        builder = ResponseBuilder()
        # response status
        builder.set_status("403", "FORBIDDEN")
        builder.add_header("Content-Type", "text/html")
        builder.add_header("Connection", "close")
        # return 403 html page in contents
        builder.set_content(get_file_contents("../html/403.html"))
        return builder.build()

    # for 200
    def resource_ok(self, file):
        ext = file.split(".")[-1]
        builder = ResponseBuilder()
        # response status
        builder.set_status("200", "OK")
        # set content type equal to mime type of our extension
        builder.add_header("Content-Type", get_file_mime_type(ext))
        builder.add_header("Connection", "close")
        # if it's a binary file, then call set_content with the input 
        # as get_file_binary_contents
        if should_return_binary(ext):
            builder.set_content(get_file_binary_contents(file))
        # otherwise, call set_content with get_file_contents
        else:
            builder.set_content(get_file_contents(file))
        return builder.build()

class ResponseBuilder:
    """
    This class is here for your use if you want to use it. This follows
    the builder design pattern to assist you in forming a response. An
    example of its use is in the `method_not_allowed` function.

    Its use is optional, but it is likely to help, and completing and using
    this function to build your responses will give 5 bonus points.
    """

    def __init__(self):
        """
        Initialize the parts of a response to nothing.
        """
        self.headers = []
        self.status = None
        self.content = None
        self.location = None

    def add_header(self, headerKey, headerValue):
        """ Adds a new header to the response """
        self.headers.append(f"{headerKey}: {headerValue}")

    def set_status(self, statusCode, statusMessage):
        """ Sets the status of the response """
        self.status = f"HTTP/1.1 {statusCode} {statusMessage}"

    def set_content(self, content):
        """ Sets `self.content` to the bytes of the content """
        if isinstance(content, (bytes, bytearray)):
            self.content = content
        else:
            self.content = content.encode("utf-8")
            
    def set_location(self, loc):
        """Sets `self.location` of the response"""
        self.location = f"Location:https://www.youtube.com/results?search_query={loc}"
        

    def build(self):
        """
        Returns the utf-8 bytes of the response.

        Uses the `self.status`, `self.headers`, `self.content` and `self.location` to form
        an HTTP response in valid formatting per w3c specifications, which
        can be seen here:
          https://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html
        or here:
          https://www.tutorialspoint.com/http/http_responses.htm

        Where CRLF is our `NEWLINE` constant.
        """

        # check if status contains any information
        if self.status:
            # add status line to response
            response = self.status + NEWLINE

            # add header lines to our response
            for i in self.headers:
                response += i + NEWLINE

            # check if anything in the contents
            if self.content:
                response += NEWLINE
                # encode response before appending encoded contents
                response = response.encode('utf-8')
                # print to screen so we can see what's going on
                print()
                print(response.decode('ascii'))
                # add contents to response
                response += self.content
                # return our response
                return response

            # for the case where there's a redirect
            elif self.location:
                # add the redirected location to our response
                response += self.location
                # print to screen
                print()
                print(response)
                # encode and return our response
                return response.encode('utf-8')

if __name__ == "__main__":
    HTTPServer()


