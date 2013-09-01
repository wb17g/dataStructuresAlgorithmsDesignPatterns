package DataStructures;

/**
 * List abstract data type.
 *
 * @author Quinn Liu (quinnliu@vt.edu)
 * @version Sep 1, 2013
 */
public interface ListInterface<E> {
    /**
     * Insert an element behind the current position. Must check that the linked
     * list's capacity is not exceeded.
     */
    public void insert(E item);

    public void append(E item);

    /**
     * Remove and return the current element.
     */
    public E remove();

    /**
     * Remove all contents from the list.
     */
    public void clear();

    public void moveToStart();

    public void moveToEnd();

    /**
     * Move the current position one element before. No change if already at the
     * beginning.
     */
    public void previous();

    /**
     * Move the current position one element after. No change if already at the
     * end.
     */
    public void next();

    /**
     * @return The number of items in the list.
     */
    public int length();

    public int currentPosition();

    public void moveCurrentNodeToPosition(int position);

    /**
     * @return The current item in the current position.
     */
    public E getValue();
}