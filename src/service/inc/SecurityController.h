/*
 * Copyright <year>  <name of author> <e-mail>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * The advertising clause requiring mention in adverts must never be included.
 */

/* $Id$ */
/*!
 * \file Controller.h
 * \brief Header of Controller
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/geo2tag
 * ---------------------------------------------------------------- */


#ifndef _Controller_H_9E63E830_D5D9_4902_B6C5_122E97EB93DB_INCLUDED_
#define _Controller_H_9E63E830_D5D9_4902_B6C5_122E97EB93DB_INCLUDED_

#include <QMap>
#include <QPair>

namespace Security
{

    class Controller{
  	typedef unsigned int Token;
        typedef unsigned int AccessRights;

        QMap< QPair<Token, Token>, AccessRights>   m_data;

  public:

        static Controller& getInstance();


    ~Controller();

		bool isAllowed( const Token& object, const Token& subject, const AccessRights& rights) const;


  private:    
    Controller();

    Controller(const Controller& obj);
    Controller& operator=(const Controller& obj);

  }; // class Controller
  
} // namespace Security

#endif //_Controller_H_9E63E830_D5D9_4902_B6C5_122E97EB93DB_INCLUDED_

/* ===[ End of file $HeadURL$ ]=== */
