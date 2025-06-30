import React from 'react';
import {Routes, Route} from 'react-router-dom';
import NavBar from './components/NavBar';
import LoginPage from './pages/LoginPage';
import RegisterPage from './pages/RegisterPage';
import FilmListPage from './pages/FilmListPage';
import FilmDetailPage from './pages/FilmDetailPage';
import NotFoundPage from './pages/NotFoundPage';
import AccountPage from './pages/AccountPage';
import UserListPage from './pages/UserListPage';
import ProtectedRoute from './routes/ProtectedRoute';

export default function App() {
	return (
		<>
			<NavBar />
			<Routes>
				<Route path="/" element={<FilmListPage />} />
				<Route path="/login" element={<LoginPage />} />
				<Route path="/register" element={<RegisterPage />} />
				<Route 
					path="/account" 
					element={
						<ProtectedRoute>
							<AccountPage />
						</ProtectedRoute>
					} 	
				/>
				<Route 
					path="/users" 
					element={
						<ProtectedRoute>
							<UserListPage />
						</ProtectedRoute>
					} 	
				/>
				<Route 
					path="/films/:id" 
					element={
						<ProtectedRoute>
							<FilmDetailPage />
						</ProtectedRoute>
					} 	
				/>
				<Route path="*" element={<NotFoundPage />} />
			</Routes>
		</>
	);
}