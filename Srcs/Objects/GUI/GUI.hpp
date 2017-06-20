//
// GUI.hpp for GUI in /home/jsx/Epitech/tek2/C++2/plazza/cpp_plazza/Srcs/Objects/GUI/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Mon Apr 10 18:38:35 2017 jsx
// Last update Fri Apr 28 22:59:33 2017 jsx
//

#ifndef GUI_HPP_
#define GUI_HPP_

# include "AUI.hpp"
# include <ctime>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# define  WINX (1280)
# define  WINY (720)

namespace plazza
{
  enum class ScreenState : int
  {
    UNKNOWN = -1,
    FILE_SELECT = 0,
    LOADBALANCER_INFO = 1,
    RESULT_LIST = 2
  };

  struct OutlineInfo
  {
    OutlineInfo(bool o, float const& t, sf::Color const& c) : isOutlined(o), thickness(t), color(c) {};

    bool      isOutlined;
    float     thickness;
    sf::Color color;
  };

  class GUI : public AUI
  {
    sf::RenderWindow              _window;
    sf::Font                      _font;

    std::string                   _filepath;
    ScreenState                   _screenState;
    bool                          _fadeCursor;
    std::clock_t                  _fadeTimeRef;
    std::map<std::string, bool>   _checkboxes;
    std::map<std::string, bool>   _popups;
    std::vector<size_t>           _wheelScrolling;

    std::vector<std::string>      _history;
    size_t                        _idxHistory;

    int                           _nbProcesses;
    std::vector<pid_t>            _pidList;
    std::vector<int>              _balanceList;


  public:
    GUI ();
    virtual ~GUI ();

    virtual void    start(ccry::CondVar *cv, int, plazza::LoadBalancerStatus & status, size_t & decrypt);

    bool            mouseclickInZone(sf::Event const& event, sf::Vector2f const& topLeft, sf::Vector2f const& bottomRight) const;
    bool            mousewheelInZone(sf::Event const& event, sf::Vector2f const& topLeft, sf::Vector2f const& bottomRight) const;
    bool            mousepositionInZone(sf::Vector2i const& mousePos, sf::Vector2f const& topLeft, sf::Vector2f const& bottomRight) const;

    void            activateCheckbox(std::string const& key);
    void            addTaskGUI();

    void            pollEvents();
    void            pollFileSelect(sf::Event const& event);
    void            pollLoadBalancerInfo(sf::Event const& event);
    void            pollResultList(sf::Event const& event);

    void            displayElems(plazza::LoadBalancerStatus & status);
    void            displayFileSelect();
    void            displayLoadBalancerInfo(plazza::LoadBalancerStatus & status);
    void            displayResultList();

    void            displayRectangle(sf::Vector2f const& pos, sf::Vector2f const& size, sf::Color const& color, OutlineInfo const& info);
    void            displayCircle(sf::Vector2f const& pos, size_t const& radius, sf::Color const& color, OutlineInfo const& info);
    void            displayText(sf::Vector2f const& pos, sf::Color const& color, std::string const& str, size_t const& size);
  };
}

#endif /* end of include guard: GUI_HPP_ */
