//
// Snake.cpp for snake in /home/jsx/Epitech/tek2/c++1/cpp_plazza/srcs/GAMES/snake/
//
// Made by jsx
// Login   <jean-sebastien.herbaux@epitech.eu>
//
// Started on  Fri Mar 24 21:26:21 2017 jsx
// Last update Fri Apr 28 22:58:36 2017 jsx
//

#include "GUI.hpp"

plazza::GUI::GUI() : _fadeCursor(false),
                     _fadeTimeRef(std::clock()),
                     _checkboxes({{"EMAIL_ADDRESS", 1}, {"PHONE_NUMBER", 0}, {"IP_ADDRESS", 0}}),
                     _popups({{"TASKS_TODO", 0}, {"TASKS_PROCESSING", 0}, {"TASKS_COMPLETED", 0}}),
                     _wheelScrolling({0, 0})
{

}

plazza::GUI::~GUI()
{

}

void    plazza::GUI::displayCircle(sf::Vector2f const& pos, size_t const& radius, sf::Color const& color, OutlineInfo const& info)
{
  sf::CircleShape circle(radius);

  circle.setPosition(pos);
  circle.setFillColor(color);
  if (info.isOutlined)
  {
    circle.setOutlineThickness(info.thickness);
    circle.setOutlineColor(info.color);
  }
  this->_window.draw(circle);
}

void    plazza::GUI::displayRectangle(sf::Vector2f const& pos, sf::Vector2f const& size, sf::Color const& color, OutlineInfo const& info)
{
  sf::RectangleShape rect(size);

  rect.setPosition(pos);
  rect.setFillColor(color);
  if (info.isOutlined)
  {
    rect.setOutlineThickness(info.thickness);
    rect.setOutlineColor(info.color);
  }
  this->_window.draw(rect);
}

void    plazza::GUI::displayText(sf::Vector2f const& pos, sf::Color const& color, std::string const& str, size_t const& size)
{
  sf::Text text(str, this->_font, size);

  text.setPosition(pos);
  text.setColor(color);
  this->_window.draw(text);
}

bool                          plazza::GUI::mouseclickInZone(sf::Event const& event, sf::Vector2f const& topLeft, sf::Vector2f const& bottomRight) const
{
  return (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left &&
          event.mouseButton.x >= topLeft.x && event.mouseButton.x <= bottomRight.x &&
          event.mouseButton.y >= topLeft.y && event.mouseButton.y <= bottomRight.y);
}

bool                          plazza::GUI::mousewheelInZone(sf::Event const& event, sf::Vector2f const& topLeft, sf::Vector2f const& bottomRight) const
{
  return (event.type == sf::Event::MouseWheelScrolled &&
          event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel &&
          event.mouseWheelScroll.x >= topLeft.x && event.mouseWheelScroll.x <= bottomRight.x &&
          event.mouseWheelScroll.y >= topLeft.y && event.mouseWheelScroll.y <= bottomRight.y);
}

bool                          plazza::GUI::mousepositionInZone(sf::Vector2i const& mousePos, sf::Vector2f const& topLeft, sf::Vector2f const& bottomRight) const
{
  return (mousePos.x >= topLeft.x && mousePos.x <= bottomRight.x &&
          mousePos.y >= topLeft.y && mousePos.y <= bottomRight.y);
}

void                          plazza::GUI::activateCheckbox(std::string const& key)
{
  this->_checkboxes.clear();
  for (auto it = this->_checkboxes.begin(); it != this->_checkboxes.end(); ++it)
    (*it).second = false;
  this->_checkboxes[key] = true;
}

void                          plazza::GUI::addTaskGUI()
{
  plazza::DataQuery query = plazza::DataQuery::UNDEFINED;
  std::vector<std::string> paths;
  paths.push_back(this->_filepath);
  for (auto it = this->_checkboxes.begin(); it != this->_checkboxes.end(); ++it)
  {
    if ((*it).second)
      {
        query = this->_map[(*it).first];
        break;
      }
  }
  Task task(query, paths);
  this->_tasksToDo.push_back(task);
  this->_cv->produce();
  this->_history.push_back(this->_filepath);
  this->_idxHistory = this->_history.size();
  this->_filepath = "";
}

void                          plazza::GUI::pollFileSelect(sf::Event const& event)
{
  if (event.type == sf::Event::TextEntered)
  {
    if (event.text.unicode == '\b' && this->_filepath != "")
      this->_filepath.erase(this->_filepath.size() - 1, 1);
    else if (event.text.unicode == '\r' && this->_filepath != "")
      this->addTaskGUI();
    else if (event.text.unicode < 128 && event.text.unicode != '\r' && event.text.unicode != '\b')
      this->_filepath += static_cast<char>(event.text.unicode);
  }
  if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down))
  {
    size_t  idxBefore = this->_idxHistory;
    if (event.key.code == sf::Keyboard::Up && this->_idxHistory > 0)
      this->_idxHistory -= 1;
    else if (event.key.code == sf::Keyboard::Down && this->_idxHistory < this->_history.size())
      this->_idxHistory += 1;
    if (idxBefore != this->_idxHistory)
    {
      if (this->_idxHistory >= this->_history.size())
        this->_filepath = "";
      else
        this->_filepath = this->_history[this->_idxHistory];
    }
  }
  if (this->mouseclickInZone(event, sf::Vector2f(170, 238), sf::Vector2f(170 + 25, 238 + 25)))
    this->activateCheckbox("EMAIL_ADDRESS");
  else if (this->mouseclickInZone(event, sf::Vector2f(170 + 360, 238), sf::Vector2f(170 + 360 + 25, 238 + 25)))
    this->activateCheckbox("PHONE_NUMBER");
  else if (this->mouseclickInZone(event, sf::Vector2f(170 + 720, 238), sf::Vector2f(170 + 720 + 25, 238 + 25)))
    this->activateCheckbox("IP_ADDRESS");
  else if (this->mouseclickInZone(event, sf::Vector2f(WINX / 2 - 100, 375), sf::Vector2f(WINX / 2 - 100 + 200, 375 + 50)) &&
           this->_filepath != "")
    this->addTaskGUI();
  else if (this->mouseclickInZone(event, sf::Vector2f(WINX / 2 - 525, 593), sf::Vector2f(WINX / 2 - 525 + 350, 593 + 50)))
  {
    this->_screenState = ScreenState::LOADBALANCER_INFO;
    this->_wheelScrolling[0] = 0;
    this->_wheelScrolling[1] = 0;
  }
  else if (this->mouseclickInZone(event, sf::Vector2f(WINX / 2 + 280, 593), sf::Vector2f(WINX / 2 + 280 + 200, 593 + 50)))
  {
    this->_screenState = ScreenState::RESULT_LIST;
    this->_wheelScrolling[0] = 0;
  }
}

void                          plazza::GUI::pollLoadBalancerInfo(sf::Event const& event)
{
  if (this->mouseclickInZone(event, sf::Vector2f(WINX / 2 - 80, 633), sf::Vector2f(WINX / 2 - 80 + 160, 633 + 50)) ||
      (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace))
    this->_screenState = ScreenState::FILE_SELECT;
  if (this->mousewheelInZone(event, sf::Vector2f(50, 110), sf::Vector2f(50 + WINX / 2 - 100, 110 + 350)))
  {
    if (this->_wheelScrolling[0] > 0 && event.mouseWheelScroll.delta > 0)
      this->_wheelScrolling[0] -= 1;
    else if (this->_pidList.size() >= 11 && this->_wheelScrolling[0] != this->_pidList.size() - 11 &&
             event.mouseWheelScroll.delta < 0)
      this->_wheelScrolling[0] += 1;
  }
  if (this->mousewheelInZone(event, sf::Vector2f(WINX / 2 + 50, 110), sf::Vector2f(WINX / 2 + 50 + WINX / 2 - 100, 110 + 350)))
  {
    if (this->_wheelScrolling[1] > 0 && event.mouseWheelScroll.delta > 0)
      this->_wheelScrolling[1] -= 1;
    else if (this->_balanceList.size() >= 11 && this->_wheelScrolling[1] != this->_balanceList.size() - 11 &&
             event.mouseWheelScroll.delta < 0)
      this->_wheelScrolling[1] += 1;
  }
}

void                          plazza::GUI::pollResultList(sf::Event const& event)
{
  if (this->mouseclickInZone(event, sf::Vector2f(WINX / 2 - 80, 633), sf::Vector2f(WINX / 2 - 80 + 160, 633 + 50)) ||
      (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace))
    this->_screenState = ScreenState::FILE_SELECT;
  if (this->mousewheelInZone(event, sf::Vector2f(50, 50), sf::Vector2f(50 + WINX - 100, 50 + 530)))
  {
    if (this->_wheelScrolling[0] > 0 && event.mouseWheelScroll.delta > 0)
      this->_wheelScrolling[0] -= 1;
    else if (this->_resultList.size() >= 17 && this->_wheelScrolling[0] != this->_resultList.size() - 17 &&
             event.mouseWheelScroll.delta < 0)
      this->_wheelScrolling[0] += 1;
  }
}

void                          plazza::GUI::pollEvents()
{
  sf::Event                   event;

  while (this->_window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed ||
        (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
      this->_window.close();
    if (this->_screenState == ScreenState::FILE_SELECT)
      this->pollFileSelect(event);
    else if (this->_screenState == ScreenState::LOADBALANCER_INFO)
      this->pollLoadBalancerInfo(event);
    else if (this->_screenState == ScreenState::RESULT_LIST)
      this->pollResultList(event);
  }
}

void                          plazza::GUI::displayFileSelect()
{
  //Status display
  this->displayCircle(sf::Vector2f(1200, 50), 15,
                      (!this->_tasksProcessing.size() && !this->_tasksToDo.size()) ? (sf::Color(0, 255, 0)) : (sf::Color(236, 162, 19)),
                      OutlineInfo(false, 0, sf::Color(0)));

  //Filepath writing..
  this->displayText(sf::Vector2f(525, 50), sf::Color(0, 0, 0), "Enter a filepath :", 32);
  this->displayRectangle(sf::Vector2f(320, 120),
                         sf::Vector2f(640, 50),
                         sf::Color(0, 0, 0),
                         OutlineInfo(false, 0, sf::Color(0)));
  this->displayText(sf::Vector2f(334, 126),
                    sf::Color(255, 255, 255),
                    this->_filepath + ((!this->_fadeCursor) ? ("_") : ("")), 28);
  //Checkboxes
  this->displayRectangle(sf::Vector2f(170, 238),
                         sf::Vector2f(25, 25),
                         sf::Color(120, 120, 120),
                         OutlineInfo(true, 3, sf::Color(90, 90, 90)));
  this->displayText(sf::Vector2f(215, 235), sf::Color(0, 0, 0), "Email addresses", 24);
  if (this->_checkboxes["EMAIL_ADDRESS"])
    this->displayText(sf::Vector2f(175, 230), sf::Color(255, 255, 255), "x", 30);
  this->displayRectangle(sf::Vector2f(170 + 360, 238),
                         sf::Vector2f(25, 25),
                         sf::Color(120, 120, 120),
                         OutlineInfo(true, 3, sf::Color(90, 90, 90)));
  this->displayText(sf::Vector2f(215 + 360, 235), sf::Color(0, 0, 0), "Phone numbers", 24);
  if (this->_checkboxes["PHONE_NUMBER"])
    this->displayText(sf::Vector2f(175 + 360, 230), sf::Color(255, 255, 255), "x", 30);
  this->displayRectangle(sf::Vector2f(170 + 720, 238),
                         sf::Vector2f(25, 25),
                         sf::Color(120, 120, 120),
                         OutlineInfo(true, 3, sf::Color(90, 90, 90)));
  this->displayText(sf::Vector2f(215 + 720, 235), sf::Color(0, 0, 0), "IP addresses", 24);
  if (this->_checkboxes["IP_ADDRESS"])
    this->displayText(sf::Vector2f(175 + 720, 230), sf::Color(255, 255, 255), "x", 30);
  //Add task button
  this->displayRectangle(sf::Vector2f(WINX / 2 - 100, 375),
                         sf::Vector2f(200, 50),
                         sf::Color(120, 120, 120),
                         OutlineInfo(true, 3, sf::Color(90, 90, 90)));
  this->displayText(sf::Vector2f(590, 385), sf::Color(255, 255, 255), "Add task", 26);
  //Load Balancer Info button
  this->displayRectangle(sf::Vector2f(WINX / 2 - 525, 593),
                         sf::Vector2f(350, 50),
                         sf::Color(120, 120, 120),
                         OutlineInfo(true, 3, sf::Color(90, 90, 90)));
  this->displayText(sf::Vector2f(183, 600), sf::Color(255, 255, 255), "Load Balancer info", 26);
  //Results button
  this->displayRectangle(sf::Vector2f(WINX / 2 + 280, 593),
                         sf::Vector2f(200, 50),
                         sf::Color(120, 120, 120),
                         OutlineInfo(true, 3, sf::Color(90, 90, 90)));
  this->displayText(sf::Vector2f(980, 600), sf::Color(255, 255, 255), "Results", 26);
}

void                          plazza::GUI::displayLoadBalancerInfo(plazza::LoadBalancerStatus & status)
{
  //Back button
  this->displayRectangle(sf::Vector2f(WINX / 2 - 80, 633),
                         sf::Vector2f(160, 50),
                         sf::Color(120, 120, 120),
                         OutlineInfo(true, 3, sf::Color(90, 90, 90)));
  this->displayText(sf::Vector2f(612, 640), sf::Color(255, 255, 255), "Back", 26);
  {
    ccry::ScopedLock   lock(&(status.mutex));
    this->_nbProcesses = status.nbProcess;
    this->_pidList = status.pids;
    this->_balanceList = status.balance;
  }
  this->displayText(sf::Vector2f(260, 45), sf::Color(0, 0, 0), "PID list :", 26);
  this->displayRectangle(sf::Vector2f(50, 110),
                         sf::Vector2f(WINX / 2 - 100, 350),
                         sf::Color(0, 0, 0),
                         OutlineInfo(true, 5, sf::Color(90, 90, 90)));

  for (size_t i = this->_wheelScrolling[0], y = 0, max = this->_wheelScrolling[0] + 11; i < this->_pidList.size() && i < max; i++, y++)
    this->displayText(sf::Vector2f(70, 123 + 30 * y), sf::Color(255, 255, 255), std::to_string(this->_pidList[i]), 20);
  this->displayText(sf::Vector2f(870, 45), sf::Color(0, 0, 0), "Usage of threads :", 26);
  this->displayRectangle(sf::Vector2f(WINX / 2 + 50, 110),
                        sf::Vector2f(WINX / 2 - 100, 350),
                        sf::Color(0, 0, 0),
                        OutlineInfo(true, 5, sf::Color(90, 90, 90)));
  for (size_t i = this->_wheelScrolling[1], y = 0, max = this->_wheelScrolling[1] + 11; i < this->_balanceList.size() && i < max; i++, y++)
    this->displayText(sf::Vector2f(WINX / 2 + 70, 123 + 30 * y), sf::Color(255, 255, 255), std::to_string(static_cast<int>((this->_nbThread * 2 - this->_balanceList[i]) / static_cast<double>(this->_nbThread * 2) * 100)) + "%", 20);
  size_t  allSize = this->_tasksToDo.size() + this->_tasksProcessing.size() + this->_tasksCompleted.size();
  size_t  todoPxSize = (!allSize) ? (0) : (700.0f * (static_cast<double>(this->_tasksToDo.size() / static_cast<double>(allSize))));
  size_t  processingPxSize = (!allSize) ? (0) : (700.0f * (static_cast<double>(this->_tasksProcessing.size() / static_cast<double>(allSize))));
  size_t  completedPxSize = (!allSize) ? (700) : (700.0f * (static_cast<double>(this->_tasksCompleted.size() / static_cast<double>(allSize))));
  sf::Vector2i mousePos = sf::Mouse::getPosition(this->_window);
  this->displayRectangle(sf::Vector2f(WINX / 2 - 350, 530),
                         sf::Vector2f(700, 55),
                         sf::Color::Transparent,
                         OutlineInfo(true, 4, sf::Color(0, 0, 0)));
  this->displayRectangle(sf::Vector2f(WINX / 2 - 350, 530),
                         sf::Vector2f(todoPxSize, 55),
                         sf::Color::Red,
                         OutlineInfo(false, 0, sf::Color::Transparent));
  this->displayRectangle(sf::Vector2f(WINX / 2 - 350 + todoPxSize, 530),
                         sf::Vector2f(processingPxSize, 55),
                         sf::Color::Yellow,
                         OutlineInfo(false, 0, sf::Color::Transparent));
  this->displayRectangle(sf::Vector2f(WINX / 2 - 350 + todoPxSize + processingPxSize, 530),
                         sf::Vector2f(completedPxSize, 55),
                         sf::Color::Green,
                         OutlineInfo(false, 0, sf::Color::Transparent));
  if (this->mousepositionInZone(mousePos, sf::Vector2f(WINX / 2 - 350, 530),
                               sf::Vector2f(WINX / 2 - 350 + todoPxSize, 530 + 55)))
   {
     this->displayRectangle(sf::Vector2f(mousePos.x, mousePos.y),
                            sf::Vector2f(200, 55),
                            sf::Color(30, 30, 30),
                            OutlineInfo(false, 0, sf::Color::Transparent));
     this->displayText(sf::Vector2f(mousePos.x + 15, mousePos.y + 15),
                       sf::Color(255, 255, 255),
                       std::to_string(this->_tasksToDo.size()) + " task" + ((this->_tasksToDo.size() != 1) ? ("s") : ("")) + " to be done", 18);
   }
  if (this->mousepositionInZone(mousePos, sf::Vector2f(WINX / 2 - 350 + todoPxSize, 530),
                                sf::Vector2f(WINX / 2 - 350 + todoPxSize + processingPxSize, 530 + 55)))
    {
      this->displayRectangle(sf::Vector2f(mousePos.x, mousePos.y),
                             sf::Vector2f(200, 55),
                             sf::Color(30, 30, 30),
                             OutlineInfo(false, 0, sf::Color::Transparent));
      this->displayText(sf::Vector2f(mousePos.x + 15, mousePos.y + 15),
                        sf::Color(255, 255, 255),
                        std::to_string(this->_tasksProcessing.size()) + " task" + ((this->_tasksProcessing.size() != 1) ? ("s") : ("")) + " processing", 18);
    }
  if (this->mousepositionInZone(mousePos, sf::Vector2f(WINX / 2 - 350 + todoPxSize + processingPxSize, 530),
                                sf::Vector2f(WINX / 2 - 350 + todoPxSize + processingPxSize + completedPxSize, 530 + 55)))
    {
      this->displayRectangle(sf::Vector2f(mousePos.x, mousePos.y),
                             sf::Vector2f(200, 55),
                             sf::Color(30, 30, 30),
                             OutlineInfo(false, 0, sf::Color::Transparent));
      this->displayText(sf::Vector2f(mousePos.x + 15, mousePos.y + 15),
                        sf::Color(255, 255, 255),
                        std::to_string(this->_tasksCompleted.size()) + " task" + ((this->_tasksCompleted.size() != 1) ? ("s") : ("")) + " done", 18);
    }
}

void                          plazza::GUI::displayResultList()
{
  //Display results
  this->displayRectangle(sf::Vector2f(50, 50),
                         sf::Vector2f(WINX - 100, 530),
                         sf::Color(0, 0, 0),
                         OutlineInfo(true, 5, sf::Color(90, 90, 90)));
  size_t max = this->_wheelScrolling[0] + 17;
  size_t i = this->_wheelScrolling[0];
  size_t y = 0;
  for (auto it = this->_resultList.rbegin() + i; it != this->_resultList.rend() && i < max; i++, y++, ++it)
  {
    std::string result;
    if ((*it)->result[0] == 0)
      result = " ";
    else
      result = "[" + std::to_string((*it)->idTask) + "]\t" + (*it)->result;
    this->displayText(sf::Vector2f(70, 65 + 30 * y), sf::Color(255, 255, 255),  result , 20);
  }
  //Back button
  this->displayRectangle(sf::Vector2f(WINX / 2 - 80, 633),
                         sf::Vector2f(160, 50),
                         sf::Color(120, 120, 120),
                         OutlineInfo(true, 3, sf::Color(90, 90, 90)));
  this->displayText(sf::Vector2f(612, 640), sf::Color(255, 255, 255), "Back", 26);
}

void                          plazza::GUI::displayElems(plazza::LoadBalancerStatus & status)
{
  this->_window.clear(sf::Color(238, 230, 209));
  if (this->_screenState == ScreenState::FILE_SELECT)
    this->displayFileSelect();
  else if (this->_screenState == ScreenState::LOADBALANCER_INFO)
    this->displayLoadBalancerInfo(status);
  else if (this->_screenState == ScreenState::RESULT_LIST)
    this->displayResultList();
  this->_window.display();
}

void                          plazza::GUI::start(ccry::CondVar *cv, int nbThread, plazza::LoadBalancerStatus & status, size_t &)
{
  this->_nbThread = nbThread;
  this->_cv = cv;
  this->_window.create(sf::VideoMode(WINX, WINY), "Plazza");
  this->_screenState = ScreenState::FILE_SELECT;
  if (!this->_font.loadFromFile("./Assets/Fonts/Oxygen.otf"))
  {
    std::cerr << "Can't load './Assets/Fonts/Oxygen.otf'" << std::endl;
    this->_window.close();
  }
  while (this->_window.isOpen())
  {
    this->readPipeTaskResultMinified(this->_tmp);
    if ((std::clock() - this->_fadeTimeRef) / 35000)
      {
        this->_fadeCursor = !this->_fadeCursor;
        this->_fadeTimeRef = std::clock();
      }
    this->pollEvents();
    this->displayElems(status);
  }
  this->stop();
}

extern "C" plazza::GUI*   CObject(void)
{
  return (new plazza::GUI);
}

extern "C" void               DObject(plazza::GUI* gui)
{
  delete gui;
}
