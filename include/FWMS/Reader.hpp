#pragma once

namespace ms {

class Message;

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

	protected:
		/** Handle incoming message.
		 * @param message Message.
		 */
		virtual void handle_message( const Message& message ) = 0;

	private:
};

}
