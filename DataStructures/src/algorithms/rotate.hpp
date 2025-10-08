namespace algorithms
{    
    template<class Iterator>
    void rotate( Iterator first, Iterator pivot, Iterator last)
    {
        Iterator next = pivot;
        while(first !=next)
        {
            swap(*first, *next++);
            if(next==last) next=middle;
            else if (first==middle) middle = next; 
        }
    }
}