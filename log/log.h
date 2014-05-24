/*
 * =====================================================================================
 *
 *       filename:  log.h
 *
 *    description:  simple log system
 *
 *        version:  1.0
 *        created:  2013-05-08
 *       revision:  none
 *       compiler:  g++
 *
 *         author:  amadeuzou
 *                  (modifed by Kun Chen)
 *        company:  blog.youtueye.com
 *
 *      copyright:  2013 amadeuzou#gmail.com. All Rights Reserved.
 *
 * =====================================================================================
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
/**
 * @brief       streambuf for null stream
 * @author      amadeu zou
 */
class NullStreamBuffer:public std::streambuf
{

public:
    NullStreamBuffer():_pos(0), _size(32)
    {
        _buf = new char[_size];
    }
    ~NullStreamBuffer()
    {
        delete[]_buf;
    }

protected:

    // central output function
    virtual int_type overflow(int_type c)
    {
        if (c != EOF)
        {

            if (_pos >= _size)
            {
                _pos %= _size;
            }

            if (c == '\n')
            {
                _pos = 0;
            }
            else  			//
            {
                _buf[_pos++] = c;
            }
        }
        return c;
    }

private:
    char *_buf;
    int _pos;
    int _size;
};

/**
 * @brief       null stream
 * @author      amadeu zou
 */
class NullStream:public std::ostream
{
public:
    NullStream():std::ostream(new NullStreamBuffer()), std::ios(0)
    {
    }
    ~NullStream()
    {
        delete rdbuf();
    }
};

// log level
enum LogLevel
{
    DEBUG = 0, INFO, WARNING, ERROR, NONE
};

// log info header
const std::string LOGSTR[5] =
{
    "[DEBUG]", "[INFO]", "[WARNING]", "[ERROR]", ""
};

/**
 * @brief       log
 * @author      amadeu zou
 */
class Logger
{

public:

    /**
     * @brief       constructor
     *
     */
    Logger():_os(&std::cerr), _level(INFO)
    {

    }
    /**
     * @brief       destructor
     *
     */ ~Logger()
    {
        _os = NULL;
    }

    /**
     * @brief       copy
     *
     */
    Logger(const Logger & log):_os(log._os), _level(log._level)
    {

    }

    /**
     * @brief       copy
     *
     */
    Logger & operator=(Logger & log)
    {
        if (this != &log)
        {
            this->_os = log._os;
            this->_level = log._level;
            this->_label = log._label;
        }

        return *this;
    }

    /**
     * @brief       set log file
     *
     * @param       log file
     */
    void set_file(const std::string & log_file)
    {
        _os = new std::ofstream(log_file.c_str());
        if (NULL == _os)
            _os = &std::cerr;
    }

    /**
     * @brief       debug log
     *
     */
    std::ostream & debug()
    {
        if (_level > DEBUG)
            return _ns;

        *_os << get_label() << get_time() << LOGSTR[DEBUG] << std::endl;
        return *_os;

    }

    /**
     * @brief       info log
     *
     */
    std::ostream & info()
    {
        if (_level > INFO)
            return _ns;

        *_os << get_label() << get_time() << LOGSTR[INFO] << std::endl;
        return *_os;

    }

    /**
     * @brief       warning log
     *
     */
    std::ostream & warning()
    {
        if (_level > WARNING)
            return _ns;

        *_os << get_label() << get_time() << LOGSTR[WARNING] << std::endl;
        return *_os;
    }

    /**
     * @brief       error log
     *
     */
    std::ostream & error()
    {
        if (_level > ERROR)
            return _ns;

        *_os << get_label() << get_time() << LOGSTR[ERROR] << std::endl;
        return *_os;

    }

    /**
     * @brief       overwrite operator
     *
     */
    friend std::ostream & operator<<(std::ostream & os, Logger & t)
    {
        return *t._os;
    }

    /**
     * @brief       get system time
     *
     */
    std::string get_time()
    {
        _time = time(NULL);
        std::string str(ctime(&_time));
        // rm /r/n
        return "[" + str.substr(0, str.length() - 1) + "]";
    }

    /**
     * @brief       get task label
     *
     */
    std::string get_label()
    {
        //the _label will be initialized as "" when the Logger object is created
        if (_label.length() == 0)
            return _label;
        else
            return "[" + _label + "]";
    }

    /**
     * @brief       set log level
     *
     */
    void set_level(int v)
    {
        _level = static_cast < LogLevel > (v);
    }

    void set_label(std::string lab)
    {
        _label = lab;
    }

private:
    std::ostream * _os;
    time_t _time;
    LogLevel _level;
    std::string _label;
    NullStream _ns;
};
#endif
