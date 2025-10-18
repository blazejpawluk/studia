import React, {useContext} from 'react';
import {Link} from 'react-router-dom';
import {AuthContext} from '../contexts/AuthContext';

export default function NavBar() {
	const {user, logout} = useContext(AuthContext);

	return (
		<nav>
			{user && 
				<>
					<span>Witaj, {user.nickname}</span> 
				</>
			}
			<div class="header-container">
				<Link class="header-button" to="/">Filmy</Link>
				{user?.role === 'admin' && <Link class="header-button" to="/users">Użytkownicy</Link>}
				{user ? (
					<>
						<Link class="header-button" to="/account">Konto</Link>
						<Link class="login-button" to="/login" onClick={logout}>Wyloguj</Link>
					</>
				) : (
					<>
						<Link class="login-button" to="/login">Logowanie</Link>
						<Link class="login-button" to="/register">Rejestracja</Link>
					</>
				)}
			</div>
		</nav>
	);
}