#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <iostream>

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(std::string s1, std::string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(std::string filename); // constructor WITH memory allocation
    ~ChatBot();
    ChatBot(const ChatBot &);

    //// STUDENT CODE
    ////
    ChatBot& operator=(const ChatBot &source){
        std::cout << "Copy asignment Constructor Called" << std::endl;
        if (this == &source){
            return *this;
        }

        if (_image != NULL){
            delete _image;
            _image = NULL;
        }

        if (source._image != NULL){
            _image = new wxBitmap(*source._image);
        }
        _chatLogic = source._chatLogic;
        _rootNode = source._rootNode;
        _currentNode = source._currentNode;
        return *this;
    };
    
    ChatBot& operator=(ChatBot &&source){
        std::cout << "Move assigment Constructor Called" << std::endl;
        if (this == &source){return *this;}

        _chatLogic = source._chatLogic;
        _rootNode = source._rootNode;
        _currentNode = source._currentNode;
        _image = source._image;

        source._chatLogic = nullptr;
        source._rootNode = nullptr;
        source._currentNode = nullptr;
        source._image = NULL;
        return *this;
    };

    ChatBot(ChatBot &&);
    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { _rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { _chatLogic = chatLogic; }
    ChatLogic* GetChatLogicHandle() { return _chatLogic; }
    wxBitmap *GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(std::string message);
};

#endif /* CHATBOT_H_ */