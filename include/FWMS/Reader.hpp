#pragma once

namespace ms {

class Message;
class Router;

/** Reader baseclass.
 * The reader receives messages.
 */
class Reader {
	public:
		/** Ctor.
		 */
		Reader();

		/** Dtor.
		 */
		virtual ~Reader();

		/** Pass message.
		 * @param message Message
		 */
		void pass_message( const Message& message );

		/** Set parent router (called internally).
		 * @param router Router.
		 */
		void set_router( Router* router );

		/** Get parent router.
		 * The parent router can be used to pass message into the message system
		 * from a reader. Always check if there's a parent router set!
		 * @return Router or nullptr if no parent router set.
		 */
		Router* get_router() const;

	protected:
		/** Handle incoming message.
		 * @param message Message.
		 */
		virtual void handle_message( const Message& message ) = 0;

	private:
		Router* m_router;
};

}
